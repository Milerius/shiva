//
// Created by roman Sztergbaum on 15/06/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <shiva/ecs/system.hpp>

namespace shiva::plugins
{
    class render_system : public shiva::ecs::post_update_system<render_system>
    {
    public:
        reflect_class(render_system)

    public:
        render_system(shiva::entt::dispatcher& dispatcher, shiva::entt::entity_registry &registry) noexcept :
        system(dispatcher, registry)
        {

        }

        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry) noexcept;
        void update() noexcept final;

    private:
        //TODO: Parse a config file
        sf::RenderWindow win{sf::VideoMode(800, 600), "SFML window"};
    };
}