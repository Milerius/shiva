//
// Created by roman Sztergbaum on 12/07/2018.
//

#pragma once

#include <type_traits>
#include <shiva/entt/entt.hpp>
#include <shiva/event/all.hpp>
#include <shiva/ecs/components/all.hpp>
#include <shiva/meta/list.hpp>

namespace shiva::entt::details
{
    template <typename Component>
    static inline void
    init_component(shiva::entt::entity_registry &registry,
                   [[maybe_unused]] shiva::entt::entity_registry::entity_type entity) noexcept
    {
        registry.type<Component>();
        if constexpr (std::is_default_constructible_v<Component>)
            registry.assign<Component>(entity);
    }

    template <typename Event>
    static inline void init_event(shiva::entt::dispatcher &dispatcher) noexcept
    {
        static_assert(std::is_default_constructible_v<Event>, "Event must be default constructible");
        dispatcher.sink<Event>();
    }

    template <typename ... Types>
    static inline void
    init_components(shiva::entt::entity_registry &registry, shiva::entt::entity_registry::entity_type entity,
                    meta::type_list<Types...>)
    {
        (init_component<Types>(registry, entity), ...);
    }

    template <typename ... Types>
    static inline void init_events(shiva::entt::dispatcher &dispatcher, meta::type_list<Types...>)
    {
        (init_event<Types>(dispatcher), ...);
    }

    static inline void init_library(shiva::entt::entity_registry &registry, shiva::entt::dispatcher &dispatcher)
    {
        auto id = registry.create();
        init_events(dispatcher, shiva::event::common_events_list{});
        init_components(registry, id, shiva::ecs::common_components{});
        //registry.destroy_entity(id);
    }
}