//
// Created by roman Sztergbaum on 19/07/2018.
//

#include <boost/dll.hpp>
#include <shiva/sfml/resources/system-sfml-resources.hpp>

namespace shiva::plugins
{
    std::unique_ptr<shiva::ecs::base_system>
    resources_system::system_creator(entt::dispatcher &dispatcher, entt::entity_registry &registry,
                                     const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::resources_system>(dispatcher, registry, fixed_delta_time);
    }

    void resources_system::update() noexcept
    {
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::resources_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
