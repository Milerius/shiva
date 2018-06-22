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

    class entity_registry
    {
    public:
        using entity_type = ::entt::DefaultRegistry::entity_type;

        template <typename Func>
        void each(Func func) const
        {
            internal_registry_.each(func);
        }

        void destroy(const entity_type entity)
        {
            internal_registry_.destroy(entity);
        }

        entity_type create() noexcept
        {
            return internal_registry_.create();
        }

        template <typename Component>
        const Component &get(const entity_type entity) const noexcept
        {
            return internal_registry_.get<Component>(entity);
        }

        template <typename Component>
        Component &get(const entity_type entity) noexcept
        {
            return internal_registry_.get<Component>(entity);
        }

        template <typename Component, typename... Args>
        Component &assign(const entity_type entity, Args &&... args)
        {
            return internal_registry_.assign<Component>(entity, std::forward<Args>(args)...);
        }

        template<typename... Component>
        bool has(const entity_type entity) const noexcept
        {
            return (internal_registry_.has<Component>(entity) && ...);
        }

        template<typename Component>
        void remove(const entity_type entity)
        {
            internal_registry_.remove<Component>(entity);
        }


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

    private:
        ::entt::DefaultRegistry internal_registry_;
    };
}