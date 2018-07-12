//
// Created by roman Sztergbaum on 12/07/2018.
//

#pragma once

#include <type_traits>
#include <shiva/entt/entt.hpp>
#include <shiva/event/all.hpp>
#include <shiva/meta/list.hpp>

namespace shiva::entt
{
    template <typename Component>
    void init_component() noexcept
    {
    }

    template <typename Event>
    void init_event(shiva::entt::dispatcher &dispatcher) noexcept
    {
        static_assert(std::is_default_constructible_v<Event>, "Event must be default constructible");
        dispatcher.sink<Event>();
    }

    template <typename ... Types>
    void init_components(shiva::entt::entity_registry &registry, meta::type_list<Types...>)
    {
        (init_component<Types>(registry), ...);
    }

    template <typename ... Types>
    void init_events(shiva::entt::dispatcher &dispatcher, meta::type_list<Types...>)
    {
        (init_event<Types>(dispatcher), ...);
    }

    void init_library([[maybe_unused]] shiva::entt::entity_registry &registry, shiva::entt::dispatcher &dispatcher)
    {
        init_events(dispatcher, shiva::event::common_events_list{});
    }
}