//
// Created by roman Sztergbaum on 19/07/2018.
//

#include <boost/dll.hpp>
#include <shiva/sfml/resources/system-sfml-resources.hpp>

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
            auto& current_loaded = resources_registry_.get_nb_current_files_loaded_();
            auto& nb_files = resources_registry_.get_nb_files();
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
        state_ = static_cast<sol::state *>(user_data_);
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
            auto &drawable = entity_registry_.assign<shiva::ecs::drawable>(entity_id,
                                                                           std::make_shared<sf::Sprite>());
            return std::make_tuple(entity_id, std::static_pointer_cast<sf::Sprite>(drawable.drawable_));
        };

        (*state_)[entity_registry_.class_name()]["create_text"] = [this]([[maybe_unused]] shiva::entt::entity_registry& self,
                                                                         const char *text,
                                                                         const char *font_name,
                                                                         unsigned int size) {
            auto entity_id = this->entity_registry_.create();
            auto &drawable = entity_registry_.assign<shiva::ecs::drawable>(entity_id,
                                                                           std::make_shared<sf::Text>());
            auto text_ptr = std::static_pointer_cast<sf::Text>(drawable.drawable_);
            text_ptr->setFont(resources_registry_.get_font(font_name));
            text_ptr->setString(sf::String(text));
            text_ptr->setCharacterSize(size);

            //! TODO: Remove this latter
            text_ptr->setPosition(1920 / 2, 1080 / 2);
            return entity_id;
        };
        (*state_)["shiva"]["resource_registry"] = std::ref(resources_registry_);
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::resources_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
