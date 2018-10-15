//
// Created by avendel on 11.10.2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>
#include <shiva/input/mouse.hpp>

namespace shiva::event
{
    struct mouse_wheel_scrolled
    {
        mouse_wheel_scrolled() noexcept = default;

        mouse_wheel_scrolled(shiva::input::mouse::Wheel wheel, float delta, int x, int y) noexcept
            : wheel(wheel), delta(delta), x(x), y(y)
        {
        }

        reflect_class(mouse_wheel_scrolled)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&mouse_wheel_scrolled::wheel),
                                 reflect_member(&mouse_wheel_scrolled::delta),
                                 reflect_member(&mouse_wheel_scrolled::x),
                                 reflect_member(&mouse_wheel_scrolled::y));
        }

        shiva::input::mouse::Wheel wheel;
        float   delta;
        int     x;
        int     y;
    };
}
