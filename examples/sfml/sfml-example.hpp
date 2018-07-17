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
        ~example_world() noexcept override
        {

        }

        example_world() noexcept
        {
            system_manager_.load_plugins();
            auto &lua_system = system_manager_.create_system<shiva::scripting::lua_system>();
            lua_system.register_entity_registry();
            lua_system.register_components(shiva::ecs::common_components{});
            lua_system.register_world();
            auto render_system = system_manager_.get_system_by_name("render_system", shiva::ecs::system_type::post_update);
            auto input_system = system_manager_.get_system_by_name("input_system", shiva::ecs::system_type::pre_update);
            input_system->set_user_data(render_system->get_user_data());
            lua_system.load_all_scripted_systems();
        }
    };
}
