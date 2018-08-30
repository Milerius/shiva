//
// Created by roman Sztergbaum on 27/05/2018.
//

#pragma once

#include <shiva/ecs/system_manager.hpp>
#include <shiva/error/general_error_handler.hpp>
#include "window_config.hpp"

namespace shiva
{
    class world
    {
    public:
        //! Destructor
        ~world() noexcept = default;

        //! Constructors
#if defined(DEBUG)

        world(fs::path plugin_path = fs::current_path() /= "Debug/systems",
              const std::string library_pattern_matching = "shiva-system") noexcept :
            plugins_registry_(std::move(plugin_path), std::move(library_pattern_matching))
        {
#if defined(_WIN32)
            SetDllDirectoryA(plugin_path.string().c_str());
#endif
            dispatcher_.sink<shiva::event::quit_game>().connect(this);
            dispatcher_.sink<shiva::event::window_config_update>().connect(this);
        }

#elif defined(RELEASE)
        world(fs::path plugin_path = fs::current_path() /= "Release/systems",
            const std::string library_pattern_matching = "shiva-system") noexcept :
            plugins_registry_(std::move(plugin_path), std::move(library_pattern_matching))
                {
#if defined(_WIN32)
                        SetDllDirectoryA(plugin_path.string().c_str());
#endif
                    dispatcher_.sink<shiva::event::quit_game>().connect(this);
                    dispatcher_.sink<shiva::event::window_config_update>().connect(this);

                }
#endif

        //! Public member functions
        int run() noexcept
        {
            if (!system_manager_.nb_systems() || init_corrupted) {
                return game_return_value_;
            }
            dispatcher_.trigger<shiva::event::start_game>();
            is_running = true;
            while (is_running) {
                system_manager_.update();
            }
            return game_return_value_;
        }

        //! Callbacks
        void receive(const shiva::event::quit_game &evt) noexcept
        {
            is_running = false;
            init_corrupted = true;
            game_return_value_ = evt.return_value_;
        }

        void receive(const shiva::event::window_config_update &evt) noexcept
        {
            auto[name, size, vsync, fullscreen, native_resolution] = evt.cfg;
            window_cfg_.name = std::move(name);
            window_cfg_.size = std::move(size);
            window_cfg_.vsync = vsync;
            window_cfg_.fullscreen = fullscreen;
            window_cfg_.native_resolution = native_resolution;
        }

        //! Order declaration here is very important.
        //! Sorry for the spamming of private/protected
    private:
        //! Private typedefs
        using plugins_registry_t = shiva::helpers::plugins_registry<shiva::ecs::system_manager::pluginapi_create_t>;

        //! Private data members (prologue)
        plugins_registry_t plugins_registry_;
    protected:
        //! Protected data members (prologue)
        shiva::windows_config window_cfg_;
        shiva::entt::dispatcher dispatcher_;
        shiva::entt::entity_registry entity_registry_;
    private:
        //! Private data members (part2)
        shiva::error::general_handler error_handler{dispatcher_, entity_registry_};
    protected:
        //! Protected data members (epilogue)
        shiva::ecs::system_manager system_manager_{dispatcher_, entity_registry_, plugins_registry_};
    private:
        //! Private data members (epilogue)
        bool is_running{false};
        bool init_corrupted{false};
        int game_return_value_{0};
    };
}
