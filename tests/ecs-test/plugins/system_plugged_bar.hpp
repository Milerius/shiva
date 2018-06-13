//
// Created by roman Sztergbaum on 10/06/2018.
//

#pragma once

#include <EASTL/unique_ptr.h>
#include <shiva/stacktrace/stacktrace.hpp>
#include <shiva/entt/entt.hpp>
#include <shiva/ecs/system.hpp>

namespace shiva::testing::plugins
{
    class bar_system final : public shiva::ecs::pre_update_system<bar_system>
    {
    public:
        reflect_class(bar_system)

    public:
        bar_system(entt::dispatcher &dispatcher,
                   entt::entity_registry &registry) noexcept : system(dispatcher, registry)
        {
        }

        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                         entt::entity_registry &registry) noexcept;
        void update() noexcept final;
    };
}
