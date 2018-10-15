//
// Created by roman Sztergbaum on 17/07/2018.
//

#pragma once

#include <type_traits>

#include <shiva/reflection/reflection.hpp>
#include <shiva/input/keyboard.hpp>

namespace shiva::event
{
    struct key_pressed
    {
        key_pressed() noexcept = default;

        key_pressed(shiva::input::keyboard::TKey key, shiva::input::keyboard::Modifers modifers) noexcept
            : keycode(key), modifers_(modifers)
        {
        }

        [[deprecated]]
        key_pressed(shiva::input::keyboard::TKey key,
            bool alt_,
            bool control_,
            bool shift_,
            bool system_) noexcept
            : keycode(key), alt(alt_), control(control_), shift(shift_), system(system_)
        {
        }

        reflect_class(key_pressed)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&key_pressed::keycode),
                                 reflect_member(&key_pressed::modifers_),
                                 reflect_member(&key_pressed::alt),
                                 reflect_member(&key_pressed::control),
                                 reflect_member(&key_pressed::shift),
                                 reflect_member(&key_pressed::system));
        }

        shiva::input::keyboard::TKey keycode{shiva::input::keyboard::Key::A};
        shiva::input::keyboard::Modifers modifers_;
        bool alt{false};
        bool control{false};
        bool shift{false};
        bool system{false};
    };
}
