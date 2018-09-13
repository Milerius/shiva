//
// Created by roman Sztergbaum on 30/08/2018.
//

#pragma once

#include <imgui.h>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/lua/lua_helpers.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/world/window_config.hpp>
#include "IconsFontAwesome5.h"

namespace shiva::editor
{
    class editor_gui : public shiva::ecs::post_update_system<editor_gui>
    {
    public:
        reflect_class(editor_gui)

        //! Callback
        void receive([[maybe_unused]] const shiva::event::after_load_resources &evt);

        //! Constructor
        editor_gui(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                       const float &fixed_delta_time, shiva::windows_config &win_cfg, sol::state &state) noexcept;

        //! Public member functions
        void update() noexcept override;

        void load_editor_resources() noexcept;
    private:
        bool resources_ready{false};
        shiva::windows_config &win_cfg_;
        sol::state &state_;


        //! Widgets
        float widget_main_menu_bar_() noexcept;
        void widget_working_tree_(float height) noexcept;
    };
}
