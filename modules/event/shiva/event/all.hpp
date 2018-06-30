//
// Created by roman Sztergbaum on 30/06/2018.
//

#pragma once

#include <shiva/event/add_base_system.hpp>
#include <shiva/event/after_load_systems_plugins.hpp>
#include <shiva/event/destruct_callback_scripted_systems.hpp>
#include <shiva/event/fatal_error_occured.hpp>
#include <shiva/event/quit_game.hpp>
#include <shiva/event/start_game.hpp>

#include <shiva/meta/list.hpp>

namespace shiva::event
{
    using common_events_list = meta::type_list<
        add_base_system,
        after_load_systems_plugins,
        fatal_error_occured,
        quit_game,
        start_game>;
}

