//
// Created by roman Sztergbaum on 18/07/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>
#include <shiva/input/mouse.hpp>

namespace shiva::event
{
    struct mouse_button_released
    {
        mouse_button_released() noexcept = default;

        mouse_button_released(shiva::input::mouse::Button button, int x, int y) noexcept
            : button(button), x(x), y(y)
        {
        }

        reflect_class(mouse_button_released)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&mouse_button_released::button),
                                 reflect_member(&mouse_button_released::x),
                                 reflect_member(&mouse_button_released::y));
        }

        shiva::input::mouse::Button button;
        int x;
        int y;
    };
}

