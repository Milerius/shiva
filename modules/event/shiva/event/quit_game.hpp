//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>

namespace shiva::event
{
    struct quit_game
    {
        using constructor_arg_type_t = int;

        quit_game(int return_value) noexcept : return_value_(return_value) //NOLINT
        {
        }

        quit_game() noexcept : return_value_(0)
        {

        }

        reflect_class(quit_game)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        int return_value_;
    };
}
