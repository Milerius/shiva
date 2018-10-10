//
// Created by roman Sztergbaum on 17/07/2018.
//

#pragma once

#include <type_traits>

#include <shiva/reflection/reflection.hpp>
#include <shiva/input/keyboard.hpp>

namespace shiva::event
{
    enum class Modifers : unsigned char {
        alt = 0,
        control,
        shift,
        system
    };

    using T = std::underlying_type_t <Modifers>;

    inline Modifers operator | (Modifers lhs, Modifers rhs)
    {
        return (Modifers)(static_cast<T>(lhs) | static_cast<T>(rhs));
    }

    inline Modifers& operator |= (Modifers& lhs, Modifers rhs)
    {
        lhs = (Modifers)(static_cast<T>(lhs) | static_cast<T>(rhs));
        return lhs;
    }

    struct key_pressed
    {
        key_pressed() noexcept = default;


        key_pressed(shiva::input::keyboard::TKey key, Modifers modifers) noexcept
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
        Modifers modifers_;
        bool alt{false};
        bool control{false};
        bool shift{false};
        bool system{false};
    };
}
