//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>
#include <shiva/event/invoker.hpp>

namespace shiva::event
{
    struct quit_game
    {
        static constexpr const shiva::event::invoker_dispatcher<quit_game, int> invoker{};

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
