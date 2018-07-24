//
// Created by roman Sztergbaum on 17/07/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>
#include <shiva/input/keyboard.hpp>

namespace shiva::event
{
    struct key_pressed
    {
        key_pressed() noexcept = default;

        key_pressed(shiva::input::keyboard::TKey key) noexcept : keycode(key)
        {

        }

        reflect_class(key_pressed)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&key_pressed::keycode));
        }

        shiva::input::keyboard::TKey keycode{shiva::input::keyboard::Key::A};
    };
}
