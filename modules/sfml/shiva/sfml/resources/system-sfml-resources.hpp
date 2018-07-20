//
// Created by roman Sztergbaum on 19/07/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/entt/entt_config.hpp>
#include "sfml-resources-registry.hpp"
#include <array>
#if defined(fmt)
#undef fmt
#include <sol/state.hpp>
#else
#include <sol/state.hpp>
#endif

namespace shiva::plugins
{
    class resources_system final : public shiva::ecs::pre_update_system<resources_system>
    {
    private:
        template <typename T>
        void register_type() noexcept
        {
            const auto table = std::tuple_cat(
                std::make_tuple(T::class_name()),
                T::reflected_functions(),
                T::reflected_members());

            try {
                std::apply(
                    [this](auto &&...params) {
                        this->state_->new_usertype<T>(std::forward<decltype(params)>(params)...);
                    }, table);
            }
            catch (const std::exception &error) {
                log_->error("error: {}", error.what());
                return;
            }

            log_->info("successfully registering type: {}", T::class_name());
        }

    public:
        ~resources_system() noexcept final = default;

        void on_set_user_data() noexcept final
        {
            state_ = static_cast<sol::state *>(user_data_);
            (*state_).new_usertype<sf::Texture>("sf_texture");
            (*state_).new_usertype<sf::Sprite>("sf_sprite",
                                               "set_texture", &sf::Sprite::setTexture,
                                               sol::base_classes,
                                               sol::bases<sf::Drawable, sf::Transformable>());
            register_type<sfml::resources_registry>();
            (*state_)[entity_registry_.class_name()]["create_game_object_with_sprite"] = [this]() {
                auto entity_id = this->entity_registry_.create();
                auto &drawable = entity_registry_.assign<shiva::ecs::drawable>(entity_id,
                                                                               std::make_shared<sf::Sprite>());
                return std::make_tuple(entity_id, std::static_pointer_cast<sf::Sprite>(drawable.drawable_));
            };
            (*state_)["shiva"]["resource_registry"] = std::ref(resources_registry_);
        }

        resources_system(shiva::entt::dispatcher &dispatcher,
                         shiva::entt::entity_registry &registry,
                         const float &fixed_delta_time) noexcept :
            system(dispatcher, registry, fixed_delta_time, true)
        {
        }

        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;
        void update() noexcept final;

        reflect_class(resources_system)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

    private:
        sfml::resources_registry resources_registry_;
        float progress_{0.0f};
        sol::state *state_{nullptr};
    };
}