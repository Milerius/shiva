//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <string>
#include <entt/signal/dispatcher.hpp>
#include <entt/entity/registry.hpp>
#include <shiva/reflection/reflection.hpp>
#include <shiva/meta/list.hpp>

/**
 * This module simply makes a namespace alias to use EnTT.
 * This module is represented by a cmake interface library that facilitates its handling through other modules.
 * This module contains also helpers for using EnTT across dll boundaries.
 * But also small changes to avoid situations of ambiguous code related to scripting
 */

// Using alias with good case
namespace shiva::entt
{
    using dispatcher = ::entt::Dispatcher;

    class entity_registry : public ::entt::DefaultRegistry
    {
    public:
        //! Reflection
        reflect_class(entity_registry)

        using base_class_t = ::entt::DefaultRegistry;

        static constexpr auto reflected_functions() noexcept
        {
            using namespace std::string_view_literals;
            return meta::makeMap("destroy"sv, &entity_registry::destroy_entity,
                                 reflect_function(&entity_registry::valid),
                                 reflect_function(&entity_registry::create));
        }

        void destroy_entity(const base_class_t::entity_type entity)
        {
            return base_class_t::destroy(entity);
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }
    };
}