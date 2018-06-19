//
// Created by roman Sztergbaum on 15/06/2018.
//

#pragma once

#include <shiva/world/world.hpp>

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
        }
    };
}
