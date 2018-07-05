//
// Created by roman Sztergbaum on 27/05/2018.
//

#pragma once


#if defined(__EMSCRIPTEN__)
    #include <emscripten/emscripten.h>
#endif

#include <shiva/ecs/system_manager.hpp>
#include <shiva/error/general_error_handler.hpp>

namespace shiva
{
    class world
    {
    public:
        virtual ~world() noexcept = default;

        world(fs::path plugin_path = fs::current_path() /= "systems") noexcept : plugins_registry_(
            std::move(plugin_path))
        {
    #ifdef __EMSCRIPTEN__
                EM_ASM({
                FS.chdir(process.cwd());
            });
    #endif
            dispatcher_.sink<shiva::event::quit_game>().connect(this);
        }

        int run() noexcept
        {
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
            game_return_value_ = evt.return_value_;
        }

    protected:
        using plugins_registry_t = shiva::helpers::plugins_registry<shiva::ecs::system_manager::pluginapi_create_t>;
        plugins_registry_t plugins_registry_;
        shiva::entt::dispatcher dispatcher_;
        shiva::entt::entity_registry entity_registry_;
        shiva::error::general_handler error_handler{dispatcher_, entity_registry_};
        shiva::ecs::system_manager system_manager_{dispatcher_, entity_registry_, plugins_registry_};
        bool is_running{false};
        int game_return_value_{0};
    };
}