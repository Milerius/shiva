//
// Created by roman Sztergbaum on 16/08/2018.
//

#include <boost/dll.hpp>
#include <shiva/box2d/system-box2d.hpp>
#include "system-box2d.hpp"

namespace shiva::plugins
{
    //! Constructor
    box2d_system::box2d_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                               const float &fixed_delta_time) noexcept :
        system(dispatcher, registry, fixed_delta_time, true),
        listener_(dispatcher)
    {
        world_.SetContactListener(&listener_);
    }

    //! Public static functions
    std::unique_ptr<shiva::ecs::base_system>
    box2d_system::system_creator(entt::dispatcher &dispatcher, entt::entity_registry &registry,
                                 const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::box2d_system>(dispatcher, registry, fixed_delta_time);
    }

    //! Public member function overriden
    void box2d_system::update() noexcept
    {
        this->world_.Step(this->fixed_delta_time_, 6, 2);
    }

    //! Reflection
    constexpr auto box2d_system::reflected_functions() noexcept
    {
        return meta::makeMap();
    }

    constexpr auto box2d_system::reflected_members() noexcept
    {
        return meta::makeMap();
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::box2d_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)

