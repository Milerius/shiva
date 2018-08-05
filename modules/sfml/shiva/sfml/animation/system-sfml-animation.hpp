//
// Created by roman Sztergbaum on 05/08/2018.
//

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <shiva/lua/lua_helpers.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/sfml/common/animation_component_impl.hpp>

namespace shiva::plugins
{
    class animation_system final : public shiva::ecs::logic_update_system<animation_system>
    {
    public:
        using status_t = shiva::sfml::animation_component_impl::status;
        ~animation_system() noexcept override = default;

        animation_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                         const float &fixed_delta_time) noexcept :
            system(dispatcher, registry, fixed_delta_time, true)
        {
        }

        void on_set_user_data() noexcept final
        {
            state_ = static_cast<sol::state *>(user_data_);
            shiva::lua::register_type<animation_system>(*state_, log_);
            state_->new_enum<status_t>("anim_status",
                                       {
                                           {"playing", status_t::playing},
                                           {"paused",  status_t::paused},
                                           {"stopped", status_t::stopped}
                                       });
            (*state_)["shiva"]["anim"] = std::ref(*this);
        }

        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;

        void update() noexcept final;

        const sf::IntRect &get_rect(entt::entity_registry::entity_type entity, size_t index) const noexcept;

        size_t size(entt::entity_registry::entity_type entity) const noexcept;

        void add_one_shot_animation(entt::entity_registry::entity_type entity,
                                    unsigned int nb_columns,
                                    unsigned int nb_lines,
                                    unsigned int nb_anims) noexcept;

        void add_frame(entt::entity_registry::entity_type entity, const sf::IntRect &rect) noexcept;

        void add_frames_line(entt::entity_registry::entity_type entity,
                             unsigned int numberX,
                             unsigned int numberY,
                             unsigned int line,
                             unsigned int columns) noexcept;

        void set_frame(entt::entity_registry::entity_type entity, size_t index) noexcept;

        void
        add_frames_column(entt::entity_registry::entity_type entity, int numberX, int numberY, int column) noexcept;

        entt::entity_registry::entity_type create_game_object_with_animated_sprite(status_t status,
                                                                                   double delta_time,
                                                                                   bool loop,
                                                                                   int repeat,
                                                                                   unsigned int nb_columns,
                                                                                   unsigned int nb_lines,
                                                                                   unsigned int nb_anims,
                                                                                   const char *texture) noexcept;

        status_t get_status(entt::entity_registry::entity_type entity) const noexcept;

        void set_status(entt::entity_registry::entity_type entity,
                        status_t status) noexcept;

    public:
        reflect_class(animation_system)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap(reflect_function(&animation_system::update),
                                 reflect_function(&animation_system::create_game_object_with_animated_sprite));
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

    private:
        void set_frame_internal(entt::entity_registry::entity_type entity, bool reset_time) noexcept;

        std::shared_ptr<shiva::sfml::animation_component_impl>
        get_animation_ptr(entt::entity_registry::entity_type entity) noexcept;

        const std::shared_ptr<shiva::sfml::animation_component_impl>
        get_animation_ptr(entt::entity_registry::entity_type entity) const noexcept;

        sol::state *state_{nullptr};
    };
}
