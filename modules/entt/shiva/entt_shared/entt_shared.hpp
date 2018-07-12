//
// Created by roman Sztergbaum on 12/07/2018.
//

#pragma once

#include <shiva/meta/list.hpp>
#include <shiva/entt/entt.hpp>

namespace shiva::entt_shared
{
    template <typename Component>
    void PP_API_EXPORT init_component() noexcept
    {

    }

    template <typename Event>
    void PP_API_EXPORT init_event(shiva::entt::dispatcher& dispatcher) noexcept
    {
        static_assert(std::is_default_constructible_v<Event>, "Event must be default constructible");
        dispatcher.sink<Event>();
    }

    template <typename ... Types>
    void PP_API_EXPORT init_components(shiva::entt::entity_registry &registry, meta::type_list<Types...>)
    {
        (init_component<Types>(registry), ...);
    }

    template <typename ... Types>
    void PP_API_EXPORT init_events(shiva::entt::dispatcher& dispatcher, meta::type_list<Types...>)
    {
        (init_event<Types>(dispatcher), ...);
    }

    void PP_API_EXPORT init_library(shiva::entt::entity_registry &registry, shiva::entt::dispatcher& dispatcher);
}
