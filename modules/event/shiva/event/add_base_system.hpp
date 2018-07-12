//
// Created by roman Sztergbaum on 23/06/2018.
//

#pragma once

#include <shiva/pp/pp_export.hpp>
#include <shiva/reflection/reflection.hpp>
#include <shiva/ecs/base_system.hpp>

namespace shiva::event
{
    struct PP_API_EXPORT add_base_system
    {
        add_base_system(std::unique_ptr<shiva::ecs::base_system> system_ptr_) noexcept :
        system_ptr(std::move(system_ptr_))
        {

        }

        add_base_system() noexcept : system_ptr{nullptr}
        {

        }

        reflect_class(add_base_system)

        std::unique_ptr<shiva::ecs::base_system> system_ptr;
    };
}
