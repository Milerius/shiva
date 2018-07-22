//
// Created by roman Sztergbaum on 19/07/2018.
//

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#ifdef __clang__
# undef __clang__
#include <sol/resolve.hpp>
# define __clang__ 1
#else
#include <sol/resolve.hpp>
#endif
#include <entt/resource/cache.hpp>
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
            unloading
        };

        using textures_cache = ::entt::ResourceCache<sf::Texture>;
        using musics_cache = ::entt::ResourceCache<sf::Music>;
        using sounds_cache = ::entt::ResourceCache<sf::SoundBuffer>;

    private:
        shiva::logging::logger log_{shiva::log::stdout_color_mt("resources_registry")};
        shiva::entt::dispatcher &dispatcher_;
        textures_cache textures_{};
        musics_cache musics_{};
        sounds_cache sounds_{};
        shiva::fs::path textures_path_;
        shiva::fs::path sounds_path_;
        shiva::fs::path musics_path_;
        std::atomic_uint32_t current_files_loaded_{0u};
        std::atomic_uint32_t nb_files_{0u};
        std::atomic_bool working_{false};
        tf::Taskflow tf_{std::thread::hardware_concurrency()};

    public:
        resources_registry(shiva::entt::dispatcher &dispatcher,
                           shiva::fs::path textures_path = shiva::fs::current_path() /= "assets/textures",
                           shiva::fs::path sounds_path = shiva::fs::current_path() /= "assets/sounds",
                           shiva::fs::path musics_path = shiva::fs::current_path() /= "assets/musics") noexcept :
            dispatcher_(dispatcher),
            textures_path_(std::move(textures_path)),
            sounds_path_(std::move(sounds_path)),
            musics_path_(std::move(musics_path))
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

        template <typename Identifier = const char *>
        bool unload_music(Identifier id, const std::string &original_path)
        {
            const auto identifier = musics_cache::resource_type{id};
            musics_.discard(identifier);
            log_->info("unloading resource: {0} from original_path {1}", id, original_path);
            return musics_.contains(identifier);
        }

        template <typename Identifier = const char *>
        bool unload_sound(Identifier id, const std::string &original_path)
        {
            const auto identifier = sounds_cache::resource_type{id};
            sounds_.discard(identifier);
            log_->info("unloading resource: {0} from original_path {1}", id, original_path);
            return sounds_.contains(identifier);
        }

        template <typename Identifier = const char *>
        bool unload_texture(Identifier id, const std::string &original_path)
        {
            const auto identifier = textures_cache::resource_type{id};
            textures_.discard(identifier);
            log_->info("unloading resource: {0} from original_path {1}", id, original_path);
            return textures_.contains(identifier);
        }

        template <typename Identifier = const char *, typename ... Args>
        bool load_music(Identifier id, Args &&...args)
        {
            const auto identifier = musics_cache::resource_type{id};
            return musics_.load<loader<sf::Music >>(identifier, std::forward<Args>(args)...);
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

        template <typename LoaderFunctor>
        bool work_on_resources(shiva::fs::path &current_resource_path,
                               std::string_view resource_type,
                               std::string_view resource_type_singular,
                               LoaderFunctor &&loader_functor,
                               const shiva::fs::path &additional_path,
                               work_type type = work_type::loading) noexcept
        {
            if (additional_path.empty())
                return work_on_resources(current_resource_path,
                                         resource_type,
                                         resource_type_singular,
                                         loader_functor,
                                         current_resource_path,
                                         type);
            std::string id;
            shiva::fs::path directory_path = current_resource_path;

            if (additional_path != current_resource_path) {
                directory_path = current_resource_path / additional_path;
                id = additional_path.string() + "/";
            }

            if (!shiva::fs::exists(directory_path)) {
                this->log_->error("trying to {0} resources from a non existent directory: {1}",
                                  (type == work_type::loading) ? "load" : "unload",
                                  directory_path.string());
                return false;
            }

            log_->info("{0} {1} from path: {2}", (type == work_type::loading) ? "load" : "unload", resource_type,
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
                               (type == work_type::loading) ? "loaded" : "unloaded",
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

        bool work_on_textures(const shiva::fs::path &additional_path = "", work_type type = work_type::loading) noexcept
        {
            auto loader_functor = [this](auto &&...params) {
                return this->load_texture(std::forward<decltype(params)>(params)...);
            };

            auto unloader_functor = [this](auto &&...params) {
                return this->unload_texture(std::forward<decltype(params)>(params)...);
            };

            if (type == work_type::loading) {
                return work_on_resources(textures_path_,
                                         "textures",
                                         "texture",
                                         loader_functor,
                                         additional_path,
                                         type);
            } else {
                return work_on_resources(textures_path_,
                                         "textures",
                                         "texture",
                                         unloader_functor,
                                         additional_path,
                                         type);
            }
        }

        bool work_on_musics(const shiva::fs::path &additional_path = "",
                            work_type type = work_type::loading) noexcept
        {
            auto loader_functor = [this](auto &&...params) {
                return this->load_music(std::forward<decltype(params)>(params)...);
            };

            auto unloader_functor = [this](auto &&...params) {
                return this->unload_music(std::forward<decltype(params)>(params)...);
            };
            if (type == work_type::loading) {
                return work_on_resources(musics_path_,
                                         "musics",
                                         "music",
                                         loader_functor,
                                         additional_path,
                                         type);
            } else {
                return work_on_resources(musics_path_,
                                         "musics",
                                         "music",
                                         unloader_functor,
                                         additional_path,
                                         type);
            }
        }

        bool work_on_sounds(const shiva::fs::path &additional_path = "",
                            work_type type = work_type::loading) noexcept
        {
            auto loader_functor = [this](auto &&...params) {
                return this->load_sound(std::forward<decltype(params)>(params)...);
            };

            auto unloader_functor = [this](auto &&...params) {
                return this->unload_sound(std::forward<decltype(params)>(params)...);
            };
            if (type == work_type::loading) {
                return work_on_resources(sounds_path_,
                                         "sounds",
                                         "sound",
                                         loader_functor,
                                         additional_path,
                                         type);
            } else {
                return work_on_resources(sounds_path_,
                                         "sounds",
                                         "sound",
                                         unloader_functor,
                                         additional_path,
                                         type);
            }
        }

        bool work_on_all_resources(const shiva::fs::path &additional_path = "",
                                   work_type type = work_type::loading) noexcept
        {
            working_ = true;
            nb_files_ = count_all_resources(additional_path);
            this->log_->info("nb_resources: {0}", nb_files_);

            auto[A, B, C, D] = tf_.silent_emplace(
                [this, additional_path, type]() { return this->work_on_textures(additional_path, type); },
                [this, additional_path, type]() { return this->work_on_musics(additional_path, type); },
                [this, additional_path, type]() { return this->work_on_sounds(additional_path, type); },
                [this, type]() {
                    this->log_->info("all resources have been {0}",
                                     (type == work_type::loading) ? "loaded" : "unloaded");
                    this->working_ = false;
                    this->nb_files_ = 0;
                    this->current_files_loaded_ = 0;
                    if (type == work_type::loading)
                        this->dispatcher_.trigger<shiva::event::after_load_resources>();
                });

            D.gather(A, B, C);
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
                                                     [](auto &&path) {
                                                         return shiva::fs::is_regular_file(path) &&
                                                                !shiva::fs::is_directory(path);
                                                     }));
        }

        size_t count_all_resources(const shiva::fs::path &additional_path = "") const noexcept
        {
            return nb_resources(textures_path_ / additional_path) +
                   nb_resources(sounds_path_ / additional_path) +
                   nb_resources(musics_path_ / additional_path);
        }

        sf::Music &get_music(const char *id) noexcept
        {
            const auto identifier = musics_cache::resource_type{id};
            return const_cast<sf::Music &>(*musics_.handle(identifier));
        }

        const sf::Music &get_music(const char *id) const noexcept
        {
            const auto identifier = musics_cache::resource_type{id};
            return *musics_.handle(identifier);
        }

        sf::Texture &get_texture(const char *id) noexcept
        {
            const auto identifier = textures_cache::resource_type{id};
            return const_cast<sf::Texture &>(*textures_.handle(identifier));
        }

        const sf::Texture &get_texture(const char *id) const noexcept
        {
            const auto identifier = textures_cache::resource_type{id};
            return *textures_.handle(identifier);
        }

        reflect_class(resources_registry);

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