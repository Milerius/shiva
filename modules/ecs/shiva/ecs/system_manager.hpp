//
// Created by roman Sztergbaum on 31/05/2018.
//

#pragma once

#include <EASTL/allocator_malloc.h>
#include <EASTL/vector.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/array.h>
#include <shiva/ecs/using_alias_library.hpp>
#include <shiva/ecs/base_system.hpp>
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
        explicit system_manager(const dispatcher& dispatcher, const entity_registry &registry) noexcept :
            dispatcher_(dispatcher),
            ett_registry_(registry)
        {

        }

    private:
        //TODO: Use it.
        [[maybe_unused]] system_registry systems_{{}};
        [[maybe_unused]] const dispatcher& dispatcher_;
        [[maybe_unused]] const entity_registry & ett_registry_;
    };
}