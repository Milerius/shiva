//
// Created by roman Sztergbaum on 06/06/2018.
//

#pragma once

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

// Using alias with good case
namespace shiva::ecs
{
    using dispatcher = entt::Dispatcher;
    using entity_registry = entt::DefaultRegistry;
}
