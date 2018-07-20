//
// Created by roman Sztergbaum on 18/06/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>

namespace shiva::event
{
    struct after_load_systems_plugins
    {
        reflect_class(after_load_systems_plugins)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }
    };
}
