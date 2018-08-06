//
// Created by roman Sztergbaum on 19/07/2018.
//

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#ifdef __clang__
# undef __clang__
#include <array>
#include <sol/resolve.hpp>
# define __clang__ 1
#else
#include <sol/resolve.hpp>
#endif
#include <entt/resource/cache.hpp>
#include <shiva/event/after_load_resources.hpp>
#include <shiva/entt/entt.hpp>
#include <shiva/sfml/resources/taskflow.hpp>
#include <shiva/spdlog/spdlog.hpp>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/sfml/resources/entt-sfml-loader.hpp>
#include <shiva/reflection/reflection.hpp>

namespace shiva::sfml
{
    class resources_registry
    {
    public:
        enum class work_type
        {
            loading,
            unloading,
            inactive
        };

        using textures_cache = ::entt::ResourceCache<sf::Texture>;
        using musics_cache = ::entt::ResourceCache<sf::Music>;
        using sounds_cache = ::entt::ResourceCache<sf::SoundBuffer>;
        using fonts_cache = ::entt::ResourceCache<sf::Font>;

    private:
        shiva::logging::logger log_{shiva::log::stdout_color_mt("resources_registry")};
        shiva::entt::dispatcher &dispatcher_;
        textures_cache textures_{};
        musics_cache musics_{};
        sounds_cache sounds_{};
        fonts_cache fonts_{};
        shiva::fs::path textures_path_;
        shiva::fs::path sounds_path_;
        shiva::fs::path musics_path_;
        shiva::fs::path fonts_path_;
        std::atomic_uint32_t current_files_loaded_{0u};
        std::atomic_uint32_t nb_files_{0u};
        std::atomic_bool working_{false};
        work_type current_working_type_{work_type::inactive};
        tf::Taskflow tf_{std::thread::hardware_concurrency()};

    public:
        resources_registry(shiva::entt::dispatcher &dispatcher,
                           shiva::fs::path textures_path = shiva::fs::current_path() /= "assets/textures",
                           shiva::fs::path sounds_path = shiva::fs::current_path() /= "assets/sounds",
                           shiva::fs::path musics_path = shiva::fs::current_path() /= "assets/musics",
                           shiva::fs::path fonts_path = shiva::fs::current_path() /= "assets/fonts") noexcept :
            dispatcher_(dispatcher),
            textures_path_(std::move(textures_path)),
            sounds_path_(std::move(sounds_path)),
            musics_path_(std::move(musics_path)),
            fonts_path_(std::move(fonts_path))
        {
        }

        const std::atomic_uint32_t &get_nb_current_files_loaded_() const noexcept
        {
            return current_files_loaded_;
        }

        const std::atomic_uint32_t &get_nb_files() const noexcept
        {
            return nb_files_;
        }

        const std::atomic_bool &is_working() const noexcept
        {
            return working_;
        }

        template <typename ResourceCache, typename Identifier = const char *>
        bool unload_resource(ResourceCache &resource_cache, Identifier id, const std::string &original_path) noexcept
        {
            const auto identifier = typename ResourceCache::resource_type{id};
            resource_cache.discard(identifier);
            log_->debug("unloading resource: {0} from original_path {1}", id, original_path);
            return resource_cache.contains(identifier);
        }

        template <typename Identifier = const char *>
        bool unload_music(Identifier id, const std::string &original_path) noexcept
        {
            return unload_resource<musics_cache>(musics_, id, original_path);
        }

        template <typename Identifier = const char *>
        bool unload_font(Identifier id, const std::string &original_path) noexcept
        {
            return unload_resource<fonts_cache>(fonts_, id, original_path);
        }

        template <typename Identifier = const char *>
        bool unload_sound(Identifier id, const std::string &original_path) noexcept
        {
            return unload_resource<sounds_cache>(sounds_, id, original_path);
        }

        template <typename Identifier = const char *>
        bool unload_texture(Identifier id, const std::string &original_path) noexcept
        {
            return unload_resource<textures_cache>(textures_, id, original_path);
        }

        template <typename Identifier = const char *, typename ... Args>
        bool load_music(Identifier id, Args &&...args)
        {
            const auto identifier = musics_cache::resource_type{id};
            return musics_.load<loader<sf::Music>>(identifier, std::forward<Args>(args)...);
        }

        template <typename Identifier = const char *, typename ... Args>
        bool load_texture(Identifier id, Args &&...args)
        {
            const auto identifier = textures_cache::resource_type{id};
            return textures_.load<loader<sf::Texture >>(identifier, std::forward<Args>(args)...);
        }

        template <typename Identifier = const char *, typename ... Args>
        bool load_sound(Identifier id, Args &&...args)
        {
            const auto identifier = sounds_cache::resource_type{id};
            return sounds_.load<loader<sf::SoundBuffer >>(identifier, std::forward<Args>(args)...);
        }

        template <typename Identifier = const char *, typename ... Args>
        bool load_font(Identifier id, Args &&...args)
        {
            const auto identifier = fonts_cache::resource_type{id};
            return fonts_.load<loader<sf::Font>>(identifier, std::forward<Args>(args)...);
        }

        template <typename LoaderFunctor>
        bool work_on_resources(shiva::fs::path &current_resource_path,
                               std::string_view resource_type,
                               std::string_view resource_type_singular,
                               LoaderFunctor &&loader_functor,
                               const shiva::fs::path &additional_path) noexcept
        {
            if (additional_path.empty())
                return work_on_resources(current_resource_path,
                                         resource_type,
                                         resource_type_singular,
                                         loader_functor,
                                         current_resource_path);
            std::string id;
            shiva::fs::path directory_path = current_resource_path;

            if (additional_path != current_resource_path) {
                directory_path = current_resource_path / additional_path;
                id = additional_path.string() + "/";
            }

            if (!shiva::fs::exists(directory_path)) {
                this->log_->error("trying to {0} resources from a non existent directory: {1}",
                                  (current_working_type_ == work_type::loading) ? "load" : "unload",
                                  directory_path.string());
                return false;
            }

            log_->info("{0} {1} from path: {2}", (current_working_type_ == work_type::loading) ? "load" : "unload",
                       resource_type,
                       directory_path.string());
            bool res = true;
            fs::recursive_directory_iterator endit;
            for (fs::recursive_directory_iterator it(directory_path); it != endit; ++it) {
                if (!fs::is_regular_file(*it))
                    continue;
                try {
                    std::string save = id;
                    std::string filename = it->path().filename().string();
                    std::string stem_filename = it->path().filename().stem().string();
                    if (additional_path != current_resource_path) {
                        id += stem_filename;
                    } else {
                        id = filename;
                    }
                    current_files_loaded_++;
                    res &= loader_functor(id.c_str(), it->path().string());
                    log_->info("{0} {1}: [ filename: {2}, id: {3}, path: {4} ]\nremaining file: {5} / {6}",
                               (current_working_type_ == work_type::loading) ? "loaded" : "unloaded",
                               resource_type_singular,
                               filename,
                               id,
                               it->path().string(),
                               current_files_loaded_,
                               nb_files_);
                    id = save;
                }
                catch (const shiva::fs::filesystem_error &error) {
                    this->log_->error("filesystem error occured: {0}", error.what());
                    res = false;
                    nb_files_--;
                }
                catch (const std::exception &error) {
                    this->log_->error("error occured: {0}", error.what());
                    res = false;
                    nb_files_--;
                }
            }
            return res;
        }

        template <typename Functor>
        bool work_on_textures(Functor &&functor, const shiva::fs::path &additional_path = "") noexcept
        {

            return work_on_resources(textures_path_,
                                     "textures",
                                     "texture",
                                     std::forward<Functor>(functor),
                                     additional_path);
        }

        template <typename Functor>
        bool work_on_musics(Functor &&functor, const shiva::fs::path &additional_path = "") noexcept
        {
            return work_on_resources(musics_path_,
                                     "musics",
                                     "music",
                                     std::forward<Functor>(functor),
                                     additional_path);
        }

        template <typename Functor>
        bool work_on_sounds(Functor &&functor, const shiva::fs::path &additional_path = "") noexcept
        {

            return work_on_resources(sounds_path_,
                                     "sounds",
                                     "sound",
                                     std::forward<Functor>(functor),
                                     additional_path);
        }

        template <typename Functor>
        bool work_on_fonts(Functor &&functor, const shiva::fs::path &additional_path = "") noexcept
        {

            return work_on_resources(fonts_path_,
                                     "fonts",
                                     "font",
                                     std::forward<Functor>(functor),
                                     additional_path);
        }

        bool work_on_all_resources(const shiva::fs::path &additional_path = "",
                                   work_type type = work_type::loading) noexcept
        {
            current_working_type_ = type;
            working_ = true;
            nb_files_ = static_cast<unsigned int>(count_all_resources(additional_path));
            this->log_->info("nb_resources: {0}", nb_files_);

            auto[A, B, C, D, E] = tf_.silent_emplace(
                [this, additional_path]() {
                    auto loader_functor = [this](auto &&...params) {
                        return this->load_texture(std::forward<decltype(params)>(params)...);
                    };

                    auto unloader_functor = [this](auto &&...params) {
                        return this->unload_texture(std::forward<decltype(params)>(params)...);
                    };

                    return (current_working_type_ == work_type::loading) ?
                           this->work_on_textures(loader_functor, additional_path) :
                           this->work_on_textures(unloader_functor, additional_path);
                },
                [this, additional_path]() {
                    auto loader_functor = [this](auto &&...params) {
                        return this->load_music(std::forward<decltype(params)>(params)...);
                    };

                    auto unloader_functor = [this](auto &&...params) {
                        return this->unload_music(std::forward<decltype(params)>(params)...);
                    };

                    return (current_working_type_ == work_type::loading) ?
                           this->work_on_musics(loader_functor, additional_path) :
                           this->work_on_musics(unloader_functor, additional_path);
                },
                [this, additional_path]() {
                    auto loader_functor = [this](auto &&...params) {
                        return this->load_sound(std::forward<decltype(params)>(params)...);
                    };

                    auto unloader_functor = [this](auto &&...params) {
                        return this->unload_sound(std::forward<decltype(params)>(params)...);
                    };
                    return (current_working_type_ == work_type::loading) ?
                           this->work_on_sounds(loader_functor, additional_path) :
                           this->work_on_sounds(unloader_functor, additional_path);
                },
                [this, additional_path]() {
                    auto loader_functor = [this](auto &&...params) {
                        return this->load_font(std::forward<decltype(params)>(params)...);
                    };

                    auto unloader_functor = [this](auto &&...params) {
                        return this->unload_font(std::forward<decltype(params)>(params)...);
                    };
                    return (current_working_type_ == work_type::loading) ?
                           this->work_on_fonts(loader_functor, additional_path) :
                           this->work_on_fonts(unloader_functor, additional_path);
                },
                [this, type]() {
                    this->log_->info("all resources have been {0}",
                                     (type == work_type::loading) ? "loaded" : "unloaded");
                    this->current_working_type_ = work_type::inactive;
                    this->working_ = false;
                    this->nb_files_ = 0;
                    this->current_files_loaded_ = 0;
                    if (type == work_type::loading)
                        this->dispatcher_.trigger<shiva::event::after_load_resources>();
                });

            E.gather(A, B, C, D);
            tf_.silent_dispatch();
            return true;
        }

        bool load_all_resources(std::string additional_path = "") noexcept
        {
            return work_on_all_resources(shiva::fs::path(std::move(additional_path)), work_type::loading);
        }

        bool unload_all_resources(std::string additional_path = "") noexcept
        {
            return work_on_all_resources(shiva::fs::path(std::move(additional_path)), work_type::unloading);
        }

        size_t nb_resources(const shiva::fs::path &path) const noexcept
        {
            using shiva::fs::recursive_directory_iterator;
            this->log_->info("counting file for path: {0}", path.string());
            if (!shiva::fs::exists(path))
                return 0u;
            return static_cast<size_t>(std::count_if(recursive_directory_iterator(path), recursive_directory_iterator{},
                                                     [](auto &&path_) {
                                                         return shiva::fs::is_regular_file(path_) &&
                                                                !shiva::fs::is_directory(path_);
                                                     }));
        }

        size_t count_all_resources(const shiva::fs::path &additional_path = "") const noexcept
        {
            return nb_resources(textures_path_ / additional_path) +
                   nb_resources(sounds_path_ / additional_path) +
                   nb_resources(musics_path_ / additional_path) +
                   nb_resources(fonts_path_ / additional_path);
        }

        template <typename ResourceType, typename ResourceCache>
        ResourceType &get_resource(const ResourceCache &resources, const char *id) noexcept
        {
            const auto identifier = typename ResourceCache::resource_type{id};
            return const_cast<ResourceType &>(*resources.handle(identifier));
        }

        template <typename ResourceType, typename ResourceCache>
        const ResourceType &get_resource(const ResourceCache &resources, const char *id) const noexcept
        {
            const auto identifier = typename ResourceCache::resource_type{id};
            return *resources.handle(identifier);
        }

        sf::Music &get_music(const char *id) noexcept
        {
            return get_resource<sf::Music, musics_cache>(musics_, id);
        }

        const sf::Music &get_music(const char *id) const noexcept
        {
            return get_resource<sf::Music, musics_cache>(musics_, id);
        }

        sf::Texture &get_texture(const char *id) noexcept
        {
            return get_resource<sf::Texture, textures_cache>(textures_, id);
        }

        const sf::Texture &get_texture(const char *id) const noexcept
        {
            return get_resource<sf::Texture, textures_cache>(textures_, id);
        }

        sf::Font &get_font(const char *id) noexcept
        {
            return get_resource<sf::Font, fonts_cache>(fonts_, id);
        }

        const sf::Font &get_font(const char *id) const noexcept
        {
            return get_resource<sf::Font, fonts_cache>(fonts_, id);
        }

        reflect_class(resources_registry)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap(
                "get_music_c",
                sol::resolve<
                    const sf::Music &(const char *) const>(&resources_registry::get_music),
                "get_music",
                sol::resolve<sf::Music &(const char *)>(&resources_registry::get_music),
                "get_texture_c",
                sol::resolve<const sf::Texture &(const char *) const>(&resources_registry::get_texture),
                "get_texture",
                sol::resolve<sf::Texture &(const char *)>(&resources_registry::get_texture),
                "get_font",
                sol::resolve<sf::Font &(const char *)>(&resources_registry::get_font),
                "get_font_c",
                sol::resolve<const sf::Font &(const char *) const>(&resources_registry::get_font),
                "load_all_resources",
                sol::resolve<bool(std::string)>(&resources_registry::load_all_resources),
                reflect_function(&resources_registry::unload_all_resources)
            );
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }
    };
}
