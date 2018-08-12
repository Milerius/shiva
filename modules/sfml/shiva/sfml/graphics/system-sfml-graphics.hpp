//
// Created by roman Sztergbaum on 15/06/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <shiva/entt/entt.hpp>
#include <shiva/ecs/system.hpp>

namespace shiva::plugins
{
    class render_system final : public shiva::ecs::post_update_system<render_system>
    {
    public:
        //! Destructor
        ~render_system() noexcept final = default;

        //! Constructor
        render_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                      const float &fixed_delta_time) noexcept;

        //! Public static functions
        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;

        //! Public member functions overriden
        void update() noexcept final;

        //! Reflection
        reflect_class(render_system)

        static constexpr auto reflected_functions() noexcept;

        static constexpr auto reflected_members() noexcept;

    private:
        //! Private data members
        //TODO: Parse a config file
        sf::RenderWindow win_{sf::VideoMode(1920, 1080), "SFML window"};
    };
}