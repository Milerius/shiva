//
// Created by roman Sztergbaum on 30/08/2018.
//

#pragma once

#include <shiva/event/after_system_reload_plugins.hpp>
#include <shiva/world/world.hpp>
#include "editor_gui.hpp"

namespace shiva::editor
{
    class editor : public shiva::world
    {
    public:
        void receive(const shiva::event::after_system_reload_plugins& evt) noexcept;
        editor() noexcept;
    };
}