//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>

namespace shiva::event
{
    struct PP_API_EXPORT quit_game
    {
        quit_game(int return_value) noexcept : return_value_(return_value) //NOLINT
        {
        }

        quit_game() noexcept : return_value_(0)
        {

        }

        reflect_class(quit_game)

        int return_value_;
    };
}
