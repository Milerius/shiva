//
// Created by roman Sztergbaum on 15/06/2018.
//

#pragma once

#include <shiva/world/world.hpp>
#include <shiva/lua/lua_system.hpp>

namespace shiva::examples::sfml
{
    class example_world : public shiva::world
    {
    public:
        ~example_world() noexcept = default;

        example_world() noexcept
        {
            bool res = system_manager_.load_plugins();
            if (!res) {
                std::cerr << "error loading plugins" << std::endl;

                exit(1);
            }
            auto &lua_system = system_manager_.create_system<shiva::scripting::lua_system>();
            auto render_system = system_manager_.get_system_by_name("render_system", shiva::ecs::system_type::post_update);
            auto input_system = system_manager_.get_system_by_name("input_system", shiva::ecs::system_type::pre_update);
            auto resources_system = system_manager_.get_system_by_name("resources_system", shiva::ecs::system_type::pre_update);
            auto animation_system = system_manager_.get_system_by_name("animation_system", shiva::ecs::system_type::logic_update);
            resources_system->set_user_data(&lua_system.get_state());
            animation_system->set_user_data(&lua_system.get_state());
            input_system->set_user_data(render_system->get_user_data());
            lua_system.load_all_scripted_systems();
        }
    };
}
