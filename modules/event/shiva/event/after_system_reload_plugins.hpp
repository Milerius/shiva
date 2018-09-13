//
// Created by roman Sztergbaum on 07/09/2018.
//

#pragma once

#include <shiva/ecs/base_system.hpp>
#include <shiva/reflection/reflection.hpp>

namespace shiva::event
{
    struct after_system_reload_plugins
    {
        after_system_reload_plugins(shiva::ecs::base_system *system_raw_ptr_) noexcept : system_raw_ptr(system_raw_ptr_)
        {
        }

        after_system_reload_plugins() noexcept : system_raw_ptr(nullptr)
        {
        }

        reflect_class(after_system_reload_plugins)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        shiva::ecs::base_system *system_raw_ptr;
    };
}

