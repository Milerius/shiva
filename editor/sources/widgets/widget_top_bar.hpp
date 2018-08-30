//
// Created by roman Sztergbaum on 30/08/2018.
//

#pragma once

#include <imgui.h>
#include <shiva/ecs/system.hpp>
#include <shiva/world/window_config.hpp>

namespace shiva::editor
{
    class widget_top_bar : public shiva::ecs::post_update_system<widget_top_bar>
    {
    public:
        reflect_class(widget_top_bar)

        widget_top_bar(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                       const float &fixed_delta_time, shiva::windows_config &win_cfg) noexcept :
            system(dispatcher, registry, fixed_delta_time),
            win_cfg_(win_cfg)
        {
        }

        void update() noexcept override
        {
            //ImGui::SetNextWindowPos(ImVec2{0, 0});
            ImGui::SetNextWindowSize(ImVec2{win_cfg_.size[0] / 4.f, win_cfg_.size[1] / 4.f});
            ImGui::BeginMainMenuBar();
            if (ImGui::BeginMenu("File")) {
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

    private:
        shiva::windows_config &win_cfg_;
    };
}
