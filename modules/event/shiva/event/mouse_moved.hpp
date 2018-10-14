//
// Created by avendel on 11.10.2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>
#include <shiva/input/mouse.hpp>

namespace shiva::event
{
    struct mouse_moved
    {
        mouse_moved() noexcept = default;

        mouse_moved(int x, int y) noexcept : x(x), y(y)
        {
        }

        reflect_class(mouse_moved)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&mouse_moved::x),
                                 reflect_member(&mouse_moved::y));
        }

        int x;
        int y;
    };
}
