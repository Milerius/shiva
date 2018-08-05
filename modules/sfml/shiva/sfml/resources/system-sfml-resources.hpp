//
// Created by roman Sztergbaum on 19/07/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/entt/entt_config.hpp>
#include <shiva/sfml/resources/sfml-resources-registry.hpp>
#include <shiva/lua/lua_helpers.hpp>

namespace shiva::plugins
{
    class resources_system final : public shiva::ecs::pre_update_system<resources_system>
    {
    public:
        ~resources_system() noexcept final = default;

        void on_set_user_data() noexcept final
        {
            state_ = static_cast<sol::state *>(user_data_);
            (*state_).new_enum<sfml::resources_registry::work_type>("work_type",
                                          {
                                              {"loading", sfml::resources_registry::work_type::loading},
                                              {"unloading", sfml::resources_registry::work_type::unloading}
                                          });
            (*state_).new_usertype<sf::Texture>("sf_texture");
            (*state_).new_usertype<sf::Sprite>("sf_sprite",
                                               "set_texture", &sf::Sprite::setTexture,
                                               sol::base_classes,
                                               sol::bases<sf::Drawable, sf::Transformable>());
            shiva::lua::register_type<sfml::resources_registry>(*state_, log_);

            (*state_)["shiva"]["is_key_pressed"] = [](shiva::input::keyboard::TKey key) {
                return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
            };

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
            system(dispatcher, registry, fixed_delta_time, true),
            resources_registry_(dispatcher)
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