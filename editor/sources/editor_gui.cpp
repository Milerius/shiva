//
// Created by roman Sztergbaum on 06/09/2018.
//

#include "editor_gui.hpp"

namespace shiva::editor
{
    //! Callback
    void editor_gui::receive([[maybe_unused]] const shiva::event::after_load_resources &evt)
    {
        this->resources_ready = true;
    }

    //! Constructor
    editor_gui::editor_gui(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                           const float &fixed_delta_time, shiva::windows_config &win_cfg, sol::state &state) noexcept :
        system(dispatcher, registry, fixed_delta_time),
        win_cfg_(win_cfg),
        state_(state)
    {
        this->dispatcher_.sink<shiva::event::after_load_resources>().connect(this);
        load_editor_resources();
    }

    void editor_gui::load_editor_resources() noexcept
    {
        //! Textures
        sol::table table = state_["shiva"]["resource_registry"];
        table["load_all_resources"](table, "editor_textures");

        //! Fonts
        ImGui::GetIO().Fonts->Clear();
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

    float editor_gui::widget_main_menu_bar_() noexcept
    {
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
        float height = ImGui::GetWindowHeight();
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
                ImGui::SetNextWindowPosCenter();
                ImGui::OpenPopup("Quit shiva editor ?");
            }
            if (ImGui::BeginPopupModal("Quit shiva editor ?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Do you really want to quit shiva editor ?");
                ImGui::Separator();

                //static int dummy_i = 0;
                //ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

                //static bool dont_ask_me_next_time = false;
                /*ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));
                ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
                ImGui::PopStyleVar();*/

                ImGui::SetCursorPosX((ImGui::GetWindowWidth() / 2.f) - 120.f);
                if (ImGui::Button("Yes", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                    this->dispatcher_.trigger<shiva::event::quit_game>(0);
                }
                ImGui::SetItemDefaultFocus();
                ImGui::SameLine(0.0f, 10.f);
                if (ImGui::Button("No", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
        ImGui::EndMainMenuBar();
        return height;
    }

    void editor_gui::widget_working_tree_(float height) noexcept
    {
        //TODO: move it elsewhere.
        //! Left panel
        ImGui::SetNextWindowPos(ImVec2{0, 0 + height});
        ImGui::SetNextWindowSizeConstraints(ImVec2{win_cfg_.size[0] * 0.2f,
                                                   win_cfg_.size[1] * 0.7f},
                                            ImVec2{win_cfg_.size[0] * 0.7f,
                                                   win_cfg_.size[1] * 0.8f});
        ImGui::Begin("Project", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize());
        std::function<void(const shiva::fs::path &)> functor = [&](
            const shiva::fs::path &path) {
            for (auto &&p : shiva::fs::directory_iterator(path)) {
                ImGuiTreeNodeFlags node_flags =
                    ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | 0;
                if (shiva::fs::is_directory(p.path())) {
                    using namespace std::string_literals;
                    std::string s = ICON_FA_FOLDER + " "s + p.path().filename().string().c_str();
                    if (ImGui::TreeNodeEx(p.path().filename().string().c_str(), node_flags, "%s",
                                          s.c_str())) {
                        if (ImGui::IsItemClicked()) {
                        }
                        functor(p);
                        ImGui::TreePop();
                    }
                } else {
                    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                    ImGui::TreeNodeEx(p.path().filename().string().c_str(), node_flags, "%s",
                                      p.path().filename().string().c_str());
                    if (ImGui::IsItemClicked()) {
                    }
                }
            }
        };
        functor(shiva::fs::current_path());
        ImGui::PopStyleVar();
        ImGui::End();
    }

    //! Public member functions
    void editor_gui::update() noexcept
    {
        ImGui::ShowDemoWindow();
        float height = widget_main_menu_bar_();
        widget_working_tree_(height);
    }
}