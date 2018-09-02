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
    class widget_top_bar : public shiva::ecs::post_update_system<widget_top_bar>
    {
    public:
        reflect_class(widget_top_bar)

        void receive([[maybe_unused]] const shiva::event::after_load_resources &evt)
        {
            this->resources_ready = true;
        }

        widget_top_bar(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                       const float &fixed_delta_time, shiva::windows_config &win_cfg, sol::state &state) noexcept :
            system(dispatcher, registry, fixed_delta_time),
            win_cfg_(win_cfg),
            state_(state)
        {
            this->dispatcher_.sink<shiva::event::after_load_resources>().connect(this);
            sol::table table = state_["shiva"]["resource_registry"];
            table["load_all_resources"](table, "editor_textures");

            ImGui::GetIO().Fonts->ClearFonts();
            ImGui::GetIO().Fonts->AddFontFromFileTTF(
                (shiva::fs::current_path() /= "assets/imgui/comic-sans-ms.ttf").string().c_str(), 40.f);

            // merge in icons from Font Awesome
            static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
            ImFontConfig icons_config;
            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            ImGui::GetIO().Fonts->AddFontFromFileTTF(
                (shiva::fs::current_path() /= "assets/imgui/fa-regular-400.ttf").string().c_str(), 28.f, &icons_config,
                icons_ranges);

            table = state_["shiva"]["render"];
            table["update_font"](table);
        }

        void update() noexcept override
        {
            ImGui::ShowDemoWindow();
            float height = 0.f;
            ImGui::BeginMainMenuBar();
            //! File
            if (ImGui::BeginMenu("File")) {
                ImGui::MenuItem("            ", nullptr, false, false);
                if (ImGui::BeginMenu("New")) {
                    ImGui::MenuItem("Project");
                    ImGui::EndMenu();
                }

                //! Save
                ImGui::MenuItem("Save", "CTRL-S");

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Project")) {
                ImGui::MenuItem("Build", "F9");
                ImGui::MenuItem("ReBuild", "F10");
                ImGui::MenuItem("Deploy", "CTRL-F10");
                ImGui::EndMenu();
            }

            ImGui::SameLine(win_cfg_.size[0] - win_cfg_.size[0] / 8.f);
            height = ImGui::GetWindowHeight();
            ImGui::SetCursorPosY(-height / 5.f);
            if (resources_ready) {
                sol::table table = state_["shiva"]["render"];
                //! Next
                table["imgui_image_button"](table, "editor_textures/next");
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Build Project");
                }

                table["imgui_image_button"](table, "editor_textures/exitRight");
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Deploy Project");
                }

                std::pair<unsigned int, unsigned int> size = table["get_texture_size"](table, "editor_textures/power");
                ImGui::SameLine(win_cfg_.size[0] - (size.first * 1.2f));

                bool is_clicked = table["imgui_image_button"](table, "editor_textures/power");
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Quit shiva editor");
                }
                if (is_clicked) {
                    this->dispatcher_.trigger<shiva::event::quit_game>(0);
                }
            }
            ImGui::EndMainMenuBar();

            //TODO: move it elsewhere.
            //! Left panel
            ImGui::SetNextWindowPos(ImVec2{0, 0 + height});
            ImGui::SetNextWindowSizeConstraints(ImVec2{0, 0},
                                                ImVec2{(float)(win_cfg_.size[0]),
                                                       win_cfg_.size[1] - win_cfg_.size[1] / 4.f});
            ImGui::Begin("Project", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
            static int selection_mask = (1 << 2);
            int node_clicked = -1;
            ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize());
            unsigned int idx = 0;
            std::function<void(const shiva::fs::path &, unsigned int)> functor = [&](const shiva::fs::path &path,
                                                                                     unsigned int depth) {
                for (auto &&p : shiva::fs::directory_iterator(path)) {
                    ImGuiTreeNodeFlags node_flags =
                        ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
                        ((selection_mask & (1 << idx)) ? ImGuiTreeNodeFlags_Selected : 0);
                    if (shiva::fs::is_directory(p.path())) {
                        using namespace std::string_literals;
                        std::string s = ICON_FA_FOLDER + " "s + p.path().filename().string().c_str();
                        if (ImGui::TreeNode(s.c_str())) {
                            if (ImGui::IsItemClicked())
                                node_clicked = idx;
                            functor(p, depth + 1);
                            ImGui::TreePop();
                        }
                    } else {
                        node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                        if (depth > 0) {
                            ImGui::Indent();
                        }
                        ImGui::TreeNodeEx((void *)(intptr_t)idx, node_flags, "%s",
                                          p.path().filename().string().c_str());
                        if (ImGui::IsItemClicked())
                            node_clicked = idx;
                        if (depth > 0) {
                            ImGui::Unindent();
                        }
                    }
                    ++idx;
                }
                depth -= 1;
            };
            functor(shiva::fs::current_path(), 0);
            if (node_clicked != -1) {
                // Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
                if (ImGui::GetIO().KeyCtrl)
                    selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked);           // Click to single-select
            }
            ImGui::PopStyleVar();
            ImGui::End();
        }

    private:
        bool resources_ready{false};
        shiva::windows_config &win_cfg_;
        sol::state &state_;
    };
}
