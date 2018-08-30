//
// Created by roman Sztergbaum on 15/06/2018.
//

#pragma once

#include <shiva/world/world.hpp>
#include <shiva/world/world_common_initializer.hpp>
#include <shiva/lua/lua_system.hpp>

namespace shiva::examples::sfml
{
    class example_world : public ::shiva::world
    {
    public:
        ~example_world() noexcept = default;

        example_world() noexcept
        {
            auto res = shiva::common::sfml_initializer(this->system_manager_);
            assert(res);
        }
    };
}
