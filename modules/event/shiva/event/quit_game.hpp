//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

namespace shiva::event
{
    struct quit_game
    {
        quit_game(int return_value) noexcept : return_value_(return_value) //NOLINT
        {
        }

        reflect_class(quit_game)

        int return_value_;
    };
}
