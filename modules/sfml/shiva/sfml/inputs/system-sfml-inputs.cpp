//
// Created by roman Sztergbaum on 18/06/2018.
//

#include <boost/dll.hpp>
#include <shiva/sfml/inputs/system-sfml-inputs.hpp>
#include <shiva/event/quit_game.hpp>

namespace shiva::plugins
{
    //! Constructor
    input_system::input_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                               const float &fixed_delta_time) noexcept :
        system(dispatcher, registry, fixed_delta_time, true)
    {
    }

    //! Private member functions overriden
    void input_system::on_set_user_data_() noexcept
    {
        win_ = static_cast<sf::RenderWindow *>(user_data_);
    }

    //! Public member functions overriden
    void input_system::update() noexcept
    {
        sf::Event evt{};
        if (win_ == nullptr)
            return;
        while (win_->pollEvent(evt)) {
            switch (evt.type) {
                case sf::Event::Closed:
                    dispatcher_.trigger<shiva::event::quit_game>(0);
                    break;
                case sf::Event::Resized:
                    break;
                case sf::Event::LostFocus:
                    break;
                case sf::Event::GainedFocus:
                    break;
                case sf::Event::TextEntered:
                    break;
                case sf::Event::KeyPressed:
                    dispatcher_.trigger<shiva::event::key_pressed>(
                        static_cast<shiva::input::keyboard::TKey >(evt.key.code));
                    break;
                case sf::Event::KeyReleased:
                    dispatcher_.trigger<shiva::event::key_released>(
                        static_cast<shiva::input::keyboard::TKey>(evt.key.code));
                    break;
                case sf::Event::MouseWheelMoved:
                    break;
                case sf::Event::MouseWheelScrolled:
                    break;
                case sf::Event::MouseButtonPressed:
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
                case sf::Event::MouseMoved:
                    break;
                case sf::Event::MouseEntered:
                    break;
                case sf::Event::MouseLeft:
                    break;
                case sf::Event::JoystickButtonPressed:
                    break;
                case sf::Event::JoystickButtonReleased:
                    break;
                case sf::Event::JoystickMoved:
                    break;
                case sf::Event::JoystickConnected:
                    break;
                case sf::Event::JoystickDisconnected:
                    break;
                case sf::Event::TouchBegan:
                    break;
                case sf::Event::TouchMoved:
                    break;
                case sf::Event::TouchEnded:
                    break;
                case sf::Event::SensorChanged:
                    break;
                case sf::Event::Count:
                    break;
            }
        }
    }

    //! Public static functions
    std::unique_ptr<shiva::ecs::base_system>
    input_system::system_creator(entt::dispatcher &dispatcher,
                                 entt::entity_registry &registry,
                                 const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::input_system>(dispatcher, registry, fixed_delta_time);
    }

    constexpr auto input_system::reflected_functions() noexcept
    {
        return meta::makeMap(reflect_function(&input_system::update));
    }

    constexpr auto input_system::reflected_members() noexcept
    {
        return meta::makeMap();
    }
}

//! DLL Initialization
BOOST_DLL_ALIAS(
    shiva::plugins::input_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
