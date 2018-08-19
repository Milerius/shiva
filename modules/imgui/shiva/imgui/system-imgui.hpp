//
// Created by roman Sztergbaum on 18/08/2018.
//

#pragma once

#include <shiva/lua/lua_helpers.hpp>
#include <shiva/ecs/system.hpp>

void LoadImguiBindings(lua_State* state);

namespace shiva::plugins
{
    class imgui_system final : public shiva::ecs::post_update_system<imgui_system>
    {
    public:
        //! Destructor
        ~imgui_system() noexcept final = default;

        //! Constructor
        imgui_system(shiva::entt::dispatcher &dispatcher,
                     shiva::entt::entity_registry &registry,
                     const float &fixed_delta_time) noexcept;

        //! Public static functions
        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;

        //! Public member function overriden
        void update() noexcept final;

        //! Reflection
        reflect_class(imgui_system)

        static constexpr auto reflected_functions() noexcept;

        static constexpr auto reflected_members() noexcept;
    private:
        //! Private member functions
        void on_set_user_data_() noexcept final;

        void set_white_windows_theme() noexcept;

        void set_monochrome_windows_theme() noexcept;

        void set_darcula_windows_theme() noexcept;
        sol::state* state_{nullptr};
    };
}