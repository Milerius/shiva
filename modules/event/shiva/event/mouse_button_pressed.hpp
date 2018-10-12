//
// Created by roman Sztergbaum on 17/07/2018.
//

#pragma once

#include <type_traits>

#include <shiva/reflection/reflection.hpp>
#include <shiva/input/mouse.hpp>

namespace shiva::event
{
    struct mouse_button_pressed
    {
        mouse_button_pressed() noexcept = default;

        mouse_button_pressed(shiva::input::mouse::Button button, int x, int y) noexcept
            : button(button), x(x), y(y)
        {
        }

        reflect_class(mouse_button_pressed)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&mouse_button_pressed::button),
                                 reflect_member(&mouse_button_pressed::x),
                                 reflect_member(&mouse_button_pressed::y));
        }

        shiva::input::mouse::Button button;
        int x;
        int y;
    };
}
