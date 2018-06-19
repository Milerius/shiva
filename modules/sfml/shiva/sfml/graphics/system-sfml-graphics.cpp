//
// Created by roman Sztergbaum on 15/06/2018.
//

#include <boost/dll.hpp>
#include <shiva/sfml/graphics/system-sfml-graphics.hpp>

namespace shiva::plugins
{

    std::unique_ptr<shiva::ecs::base_system> render_system::system_creator(shiva::entt::dispatcher &dispatcher,
                                                                    shiva::entt::entity_registry &registry,
                                                                    const float& fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::render_system>(dispatcher, registry, fixed_delta_time);
    }

    void shiva::plugins::render_system::update() noexcept
    {
        win_.clear(sf::Color::Red);
        sf::CircleShape shape(50);
        shape.setFillColor(sf::Color(100, 250, 50));
        win_.draw(shape);
        win_.display();
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::render_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
