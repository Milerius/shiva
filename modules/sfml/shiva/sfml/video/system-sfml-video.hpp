//
// Created by roman Sztergbaum on 19/08/2018.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <sfeMovie/Movie.hpp>
#include <shiva/lua/lua_helpers.hpp>
#include <shiva/ecs/system.hpp>
#include "video_component_impl.hpp"

namespace shiva::plugins
{
    class video_system final : public shiva::ecs::logic_update_system<video_system>
    {
    public:
        using status_t = shiva::sfml::video_component_impl::status;

        //! Destructor
        ~video_system() noexcept final = default;

        //! Constructor
        video_system(shiva::entt::dispatcher &dispatcher,
                     shiva::entt::entity_registry &registry,
                     const float &fixed_delta_time) noexcept;

        //! Public static functions
        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;
        //! Public member functions overriden
        void update() noexcept final;

        entt::entity_registry::entity_type create_game_object_with_video(status_t::EnumType status,
                                                                         const char *video_id,
                                                                         sol::function func = sol::lua_nil) noexcept;

        //! Reflection
        reflect_class(video_system)

        static constexpr auto reflected_functions() noexcept;

        static constexpr auto reflected_members() noexcept;
    private:
        //! Private member functions overriden
        void on_set_user_data_() noexcept final;

        void add_video_(entt::entity_registry::entity_type entity, status_t status, const char *video_id, sol::function func) noexcept;
        sol::state *state_{nullptr};
        sf::RenderWindow *win_{nullptr};
    };
}