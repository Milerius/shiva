//
// Created by roman Sztergbaum on 18/08/2018.
//

#include <imgui.h>
#include <boost/dll.hpp>
#include "system-imgui.hpp"

namespace shiva::plugins
{
    //! Constructor
    imgui_system::imgui_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                               const float &fixed_delta_time) noexcept : system(dispatcher, registry, fixed_delta_time,
                                                                                true)
    {
        disable();
    }

    //! Public static functions
    std::unique_ptr<shiva::ecs::base_system>
    imgui_system::system_creator(entt::dispatcher &dispatcher, entt::entity_registry &registry,
                                 const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::imgui_system>(dispatcher, registry, fixed_delta_time);;
    }

    void imgui_system::update() noexcept
    {
        ImGui::ShowTestWindow();
    }

    constexpr auto imgui_system::reflected_functions() noexcept
    {
        return meta::makeMap();
    }

    constexpr auto imgui_system::reflected_members() noexcept
    {
        return meta::makeMap();
    }

    //! Private member functions
    void imgui_system::on_set_user_data_() noexcept
    {
        state_ = static_cast<sol::state *>(user_data_);
        lua_State *raw_state = (*state_).lua_state();
        LoadImguiBindings(raw_state);
        enable();
        //set_white_windows_theme();
        //set_monochrome_windows_theme();
        set_darcula_windows_theme();
    }

    void imgui_system::set_white_windows_theme() noexcept
    {
        ImGuiStyle *style = &ImGui::GetStyle();
        int hspacing = 8;
        int vspacing = 6;
        style->DisplaySafeAreaPadding = ImVec2(0, 0);
        style->WindowPadding = ImVec2(hspacing / 2, vspacing);
        style->FramePadding = ImVec2(hspacing, vspacing);
        style->ItemSpacing = ImVec2(hspacing, vspacing);
        style->ItemInnerSpacing = ImVec2(hspacing, vspacing);
        style->IndentSpacing = 20.0f;

        style->WindowRounding = 0.0f;
        style->FrameRounding = 0.0f;

        style->WindowBorderSize = 0.0f;
        style->FrameBorderSize = 1.0f;
        style->PopupBorderSize = 1.0f;

        style->ScrollbarSize = 20.0f;
        style->ScrollbarRounding = 0.0f;
        style->GrabMinSize = 5.0f;
        style->GrabRounding = 0.0f;

        ImVec4 white = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        ImVec4 transparent = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        ImVec4 dark = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
        ImVec4 darker = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);

        ImVec4 background = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        ImVec4 text = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        ImVec4 border = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        ImVec4 grab = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
        ImVec4 header = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
        ImVec4 active = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
        ImVec4 hover = ImVec4(0.00f, 0.47f, 0.84f, 0.20f);

        style->Colors[ImGuiCol_Text] = text;
        style->Colors[ImGuiCol_WindowBg] = background;
        style->Colors[ImGuiCol_ChildBg] = background;
        style->Colors[ImGuiCol_PopupBg] = white;

        style->Colors[ImGuiCol_Border] = border;
        style->Colors[ImGuiCol_BorderShadow] = transparent;

        style->Colors[ImGuiCol_Button] = header;
        style->Colors[ImGuiCol_ButtonHovered] = hover;
        style->Colors[ImGuiCol_ButtonActive] = active;

        style->Colors[ImGuiCol_FrameBg] = white;
        style->Colors[ImGuiCol_FrameBgHovered] = hover;
        style->Colors[ImGuiCol_FrameBgActive] = active;

        style->Colors[ImGuiCol_MenuBarBg] = header;
        style->Colors[ImGuiCol_Header] = header;
        style->Colors[ImGuiCol_HeaderHovered] = hover;
        style->Colors[ImGuiCol_HeaderActive] = active;

        style->Colors[ImGuiCol_CheckMark] = text;
        style->Colors[ImGuiCol_SliderGrab] = grab;
        style->Colors[ImGuiCol_SliderGrabActive] = darker;

        style->Colors[ImGuiCol_ScrollbarBg] = header;
        style->Colors[ImGuiCol_ScrollbarGrab] = grab;
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = dark;
        style->Colors[ImGuiCol_ScrollbarGrabActive] = darker;
    }

    void imgui_system::set_monochrome_windows_theme() noexcept
    {
        ImGuiStyle& style = ImGui::GetStyle();
        style.Alpha = 1.0;
        style.ChildRounding = 3;
        style.WindowRounding = 3;
        style.GrabRounding = 1;
        style.GrabMinSize = 20;
        style.FrameRounding = 3;


        style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.40f, 0.41f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.80f, 0.80f, 0.18f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.44f, 0.80f, 0.80f, 0.27f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.44f, 0.81f, 0.86f, 0.66f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.18f, 0.21f, 0.73f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.22f, 0.29f, 0.30f, 0.71f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 1.00f, 0.68f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.36f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.65f, 0.65f, 0.46f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.01f, 1.00f, 1.00f, 0.43f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.62f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.33f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.42f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
        style.Colors[ImGuiCol_Column] = ImVec4(0.00f, 0.50f, 0.50f, 0.33f);
        style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.00f, 0.50f, 0.50f, 0.47f);
        style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.00f, 0.70f, 0.70f, 1.00f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 1.00f, 1.00f, 0.22f);
        style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.04f, 0.10f, 0.09f, 0.51f);
    }

    void imgui_system::set_darcula_windows_theme() noexcept
    {
        auto *style = &ImGui::GetStyle();
        style->WindowRounding = 5.3f;
        style->GrabRounding = style->FrameRounding = 2.3f;
        style->ScrollbarRounding = 5.0f;
        style->FrameBorderSize = 1.0f;
        style->ItemSpacing.y = 6.5f;

        style->Colors[ImGuiCol_Text]                  = {0.73333335f, 0.73333335f, 0.73333335f, 1.00f};
        style->Colors[ImGuiCol_TextDisabled]          = {0.34509805f, 0.34509805f, 0.34509805f, 1.00f};
        style->Colors[ImGuiCol_WindowBg]              = {0.23529413f, 0.24705884f, 0.25490198f, 0.94f};
        style->Colors[ImGuiCol_ChildBg]               = {0.23529413f, 0.24705884f, 0.25490198f, 0.00f};
        style->Colors[ImGuiCol_PopupBg]               = {0.23529413f, 0.24705884f, 0.25490198f, 0.94f};
        style->Colors[ImGuiCol_Border]                = {0.33333334f, 0.33333334f, 0.33333334f, 0.50f};
        style->Colors[ImGuiCol_BorderShadow]          = {0.15686275f, 0.15686275f, 0.15686275f, 0.00f};
        style->Colors[ImGuiCol_FrameBg]               = {0.16862746f, 0.16862746f, 0.16862746f, 0.54f};
        style->Colors[ImGuiCol_FrameBgHovered]        = {0.453125f, 0.67578125f, 0.99609375f, 0.67f};
        style->Colors[ImGuiCol_FrameBgActive]         = {0.47058827f, 0.47058827f, 0.47058827f, 0.67f};
        style->Colors[ImGuiCol_TitleBg]               = {0.04f, 0.04f, 0.04f, 1.00f};
        style->Colors[ImGuiCol_TitleBgCollapsed]      = {0.16f, 0.29f, 0.48f, 1.00f};
        style->Colors[ImGuiCol_TitleBgActive]         = {0.00f, 0.00f, 0.00f, 0.51f};
        style->Colors[ImGuiCol_MenuBarBg]             = {0.27058825f, 0.28627452f, 0.2901961f, 0.80f};
        style->Colors[ImGuiCol_ScrollbarBg]           = {0.27058825f, 0.28627452f, 0.2901961f, 0.60f};
        style->Colors[ImGuiCol_ScrollbarGrab]         = {0.21960786f, 0.30980393f, 0.41960788f, 0.51f};
        style->Colors[ImGuiCol_ScrollbarGrabHovered]  = {0.21960786f, 0.30980393f, 0.41960788f, 1.00f};
        style->Colors[ImGuiCol_ScrollbarGrabActive]   = {0.13725491f, 0.19215688f, 0.2627451f, 0.91f};
        style->Colors[ImGuiCol_CheckMark]             = {0.90f, 0.90f, 0.90f, 0.83f};
        style->Colors[ImGuiCol_SliderGrab]            = {0.70f, 0.70f, 0.70f, 0.62f};
        style->Colors[ImGuiCol_SliderGrabActive]      = {0.30f, 0.30f, 0.30f, 0.84f};
        style->Colors[ImGuiCol_Button]                = {0.33333334f, 0.3529412f, 0.36078432f, 0.49f};
        style->Colors[ImGuiCol_ButtonHovered]         = {0.21960786f, 0.30980393f, 0.41960788f, 1.00f};
        style->Colors[ImGuiCol_ButtonActive]          = {0.13725491f, 0.19215688f, 0.2627451f, 1.00f};
        style->Colors[ImGuiCol_Header]                = {0.33333334f, 0.3529412f, 0.36078432f, 0.53f};
        style->Colors[ImGuiCol_HeaderHovered]         = {0.453125f, 0.67578125f, 0.99609375f, 0.67f};
        style->Colors[ImGuiCol_HeaderActive]          = {0.47058827f, 0.47058827f, 0.47058827f, 0.67f};
        style->Colors[ImGuiCol_Separator]             = {0.31640625f, 0.31640625f, 0.31640625f, 1.00f};
        style->Colors[ImGuiCol_SeparatorHovered]      = {0.31640625f, 0.31640625f, 0.31640625f, 1.00f};
        style->Colors[ImGuiCol_SeparatorActive]       = {0.31640625f, 0.31640625f, 0.31640625f, 1.00f};
        style->Colors[ImGuiCol_ResizeGrip]            = {1.00f, 1.00f, 1.00f, 0.85f};
        style->Colors[ImGuiCol_ResizeGripHovered]     = {1.00f, 1.00f, 1.00f, 0.60f};
        style->Colors[ImGuiCol_ResizeGripActive]      = {1.00f, 1.00f, 1.00f, 0.90f};
        style->Colors[ImGuiCol_PlotLines]             = {0.61f, 0.61f, 0.61f, 1.00f};
        style->Colors[ImGuiCol_PlotLinesHovered]      = {1.00f, 0.43f, 0.35f, 1.00f};
        style->Colors[ImGuiCol_PlotHistogram]         = {0.90f, 0.70f, 0.00f, 1.00f};
        style->Colors[ImGuiCol_PlotHistogramHovered]  = {1.00f, 0.60f, 0.00f, 1.00f};
        style->Colors[ImGuiCol_TextSelectedBg]        = {0.18431373f, 0.39607847f, 0.79215693f, 0.90f};
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::imgui_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
