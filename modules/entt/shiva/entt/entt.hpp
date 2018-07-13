//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <string>
#include <entt/signal/dispatcher.hpp>
#include <entt/entity/registry.hpp>
#include <shiva/reflection/reflection.hpp>
#include <shiva/meta/list.hpp>

// Using alias with good case
namespace shiva::entt
{
    using dispatcher = ::entt::Dispatcher;

    class entity_registry : public ::entt::DefaultRegistry
    {
    public:
        //! Reflection
        reflect_class(entity_registry);

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