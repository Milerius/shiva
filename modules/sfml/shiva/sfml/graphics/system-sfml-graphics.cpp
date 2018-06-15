//
// Created by roman Sztergbaum on 15/06/2018.
//

#include <boost/dll.hpp>
#include <shiva/sfml/graphics/system-sfml-graphics.hpp>

namespace shiva::plugins
{

    std::unique_ptr<shiva::ecs::base_system> render_system::system_creator(shiva::entt::dispatcher &dispatcher,
                                                                    shiva::entt::entity_registry &registry) noexcept
    {
        return std::make_unique<shiva::plugins::render_system>(dispatcher, registry);
    }

    void shiva::plugins::render_system::update() noexcept
    {
        return;
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::render_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
