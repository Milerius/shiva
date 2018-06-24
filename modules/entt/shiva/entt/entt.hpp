//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <string>
#include <entt/entt.hpp>
#include <shiva/reflection/reflection.hpp>

// Using alias with good case
namespace shiva::entt
{
    using dispatcher = ::entt::Dispatcher;

    //using entity_registry = ::entt::DefaultRegistry;

    class entity_registry : public ::entt::DefaultRegistry
    {
    public:
        //! Reflection
        reflect_class(entity_registry);

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap(reflect_function(&entity_registry::destroy),
                                 reflect_function(&entity_registry::create));
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }
    };
}