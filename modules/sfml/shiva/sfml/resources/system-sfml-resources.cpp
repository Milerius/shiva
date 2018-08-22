//
// Created by roman Sztergbaum on 19/07/2018.
//

#include <boost/dll.hpp>
#include <shiva/sfml/resources/system-sfml-resources.hpp>
#include <shiva/ecs/opaque_data.hpp>
#include <shiva/sfml/common/drawable_component_impl.hpp>

namespace shiva::plugins
{
    //! Constructor
    resources_system::resources_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                                       const float &fixed_delta_time) noexcept :
        system(dispatcher, registry, fixed_delta_time, true),
        resources_registry_(dispatcher)
    {
    }

    //! Public static functions
    std::unique_ptr<shiva::ecs::base_system>
    resources_system::system_creator(entt::dispatcher &dispatcher, entt::entity_registry &registry,
                                     const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::resources_system>(dispatcher, registry, fixed_delta_time);
    }

    //! Public member functions overriden
    void resources_system::update() noexcept
    {
        if (resources_registry_.is_working()) {
            auto &current_loaded = resources_registry_.get_nb_current_files_loaded_();
            auto &nb_files = resources_registry_.get_nb_files();
            progress_ = static_cast<float>(current_loaded) / nb_files;
            log_->info("loading files: {0} / {1}, percentage: {2}%",
                       current_loaded,
                       nb_files,
                       progress_ * 100);
        }
    }

    //! Reflection
    constexpr auto resources_system::reflected_functions() noexcept
    {
        return meta::makeMap();
    }

    constexpr auto resources_system::reflected_members() noexcept
    {
        return meta::makeMap();
    }

    //! Private member functions overriden
    void resources_system::on_set_user_data_() noexcept
    {
        state_ = static_cast<sol::state *>(static_cast<shiva::ecs::opaque_data *>(user_data_)->data_1);
        win_ = static_cast<sf::RenderWindow *>(static_cast<shiva::ecs::opaque_data *>(user_data_)->data_2);
        assert(state_ != nullptr && win_ != nullptr);
        (*state_).new_enum<sfml::resources_registry::work_type>("work_type",
                                                                {
                                                                    {"loading",   sfml::resources_registry::work_type::loading},
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
            auto sprite_ptr = std::make_shared<sf::Sprite>();
            entity_registry_.assign<shiva::ecs::drawable>(entity_id,
                                                          std::make_shared<shiva::sfml::drawable_component_impl>(
                                                              sprite_ptr,
                                                              std::static_pointer_cast<sf::Drawable>(sprite_ptr),
                                                              std::static_pointer_cast<sf::Transformable>(sprite_ptr)));
            return std::make_tuple(entity_id, sprite_ptr);
        };

        (*state_)[entity_registry_.class_name()]["create_text"] = [this](
            [[maybe_unused]] shiva::entt::entity_registry &self,
            const char *text,
            const char *font_name,
            unsigned int size) {
            auto entity_id = this->entity_registry_.create();
            auto &transformable = entity_registry_.assign<shiva::ecs::transform_2d>(entity_id);
            auto text_ptr = std::make_shared<sf::Text>();
            entity_registry_.assign<shiva::ecs::drawable>(entity_id,
                                                          std::make_shared<shiva::sfml::drawable_component_impl>(
                                                              text_ptr,
                                                              std::static_pointer_cast<sf::Drawable>(text_ptr),
                                                              std::static_pointer_cast<sf::Transformable>(text_ptr)));
            text_ptr->setFont(resources_registry_.get_font(font_name));
            text_ptr->setString(sf::String(text));
            text_ptr->setCharacterSize(size);

            transformable.top = win_->getSize().x / 2.f;
            transformable.left = win_->getSize().y / 2.f;
            transformable.width = text_ptr->getGlobalBounds().width;
            transformable.height = text_ptr->getGlobalBounds().height;
            this->log_->info("Text created -> [top: {0}, left: {1}, width: {2}, height: {3}]",
                             transformable.top,
                             transformable.left,
                             transformable.width,
                             transformable.height);
            text_ptr->setPosition(transformable.top, transformable.left);
            return entity_id;
        };
        (*state_)["shiva"]["resource_registry"] = std::ref(resources_registry_);
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::resources_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
