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
        lua_State* raw_state = (*state_).lua_state();
        LoadImguiBindings(raw_state);
        enable();
    }
}


BOOST_DLL_ALIAS(
    shiva::plugins::imgui_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
