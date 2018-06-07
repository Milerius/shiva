//
// Created by roman Sztergbaum on 31/05/2018.
//

#pragma once

#include <EASTL/utility.h>
#include <EASTL/allocator_malloc.h>
#include <EASTL/vector.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/array.h>
#include <shiva/ecs/using_alias_library.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/ecs/system_type.hpp>

namespace shiva::ecs
{
    class system_manager
    {
    public:
        using system_ptr = eastl::unique_ptr<shiva::ecs::base_system>;
        using system_array = eastl::vector<system_ptr, eastl::allocator_malloc>;
        using system_registry = eastl::array<system_array, system_type::size>;
    public:
        explicit system_manager(dispatcher& dispatcher, entity_registry &registry) noexcept :
            dispatcher_(dispatcher),
            ett_registry_(registry)
        {

        }

        template <typename system, typename ... system_args>
        system& create_system(system_args &&...args)
        {
            auto creator = [this](auto &&... args){
                return eastl::make_unique<system>(this->dispatcher_, this->ett_registry_,
                        eastl::forward<decltype(args)>(args)...);
            };
            system_ptr sys = creator(eastl::forward<system_args>(args)...);
            return static_cast<system &>(add_system_<system>(eastl::move(sys)));
        }

    private:
        template <typename system>
        base_system &add_system_(system_ptr&& system) noexcept
        {
            return *systems_[system::get_system_type()].emplace_back(eastl::move(system));
        }

    private:
        system_registry systems_{{}};
        dispatcher& dispatcher_;
        entity_registry & ett_registry_;
    };
}