//
// Created by roman Sztergbaum on 30/06/2018.
//

#pragma once

#include <shiva/event/add_base_system.hpp>
#include <shiva/event/after_load_systems_plugins.hpp>
#include <shiva/event/fatal_error_occured.hpp>
#include <shiva/event/quit_game.hpp>
#include <shiva/event/start_game.hpp>
#include <shiva/event/key_released.hpp>
#include <shiva/event/key_pressed.hpp>
#include <shiva/event/after_load_resources.hpp>

#include <shiva/meta/list.hpp>


namespace shiva::event
{
    template <typename T>
    using has_get_data = decltype(std::declval<T &>().get_data());

    template <typename T>
    using has_get_data_t = meta::is_detected<has_get_data, T>;

    template <typename T>
    static inline constexpr bool has_get_data_v = has_get_data_t<T>::value;

    using common_events_list = meta::type_list<
        add_base_system,
        after_load_systems_plugins,
        fatal_error_occured,
        quit_game,
        start_game,
        key_pressed,
        key_released,
        after_load_resources>;
}

