//
// Created by roman Sztergbaum on 23/06/2018.
//

#pragma once

#include <shiva/ecs/base_system.hpp>

namespace shiva::event
{
    struct add_base_system
    {
        add_base_system(std::unique_ptr<shiva::ecs::base_system> system_ptr_) noexcept :
        system_ptr(std::move(system_ptr_))
        {

        }

        std::unique_ptr<shiva::ecs::base_system> system_ptr;
    };
}
