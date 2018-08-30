//
// Created by roman Sztergbaum on 30/08/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>
#include <shiva/event/invoker.hpp>

namespace shiva::event
{
    struct window_config_update
    {
        using window_config = std::tuple<std::string, std::array<unsigned int, 2>, bool, bool, bool>;
        static constexpr const shiva::event::invoker_dispatcher<window_config_update, window_config> invoker{};

        window_config_update(window_config cfg_) noexcept : cfg(std::move(cfg_))
        {
        }

        window_config_update() = default;

        reflect_class(window_config_update)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        window_config cfg{};
    };
}