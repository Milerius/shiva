//
// Created by roman Sztergbaum on 10/06/2018.
//

#pragma once

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
                   entt::entity_registry &registry,
                   const float &fixed_delta_time) noexcept : system(dispatcher, registry, fixed_delta_time)
        {
        }

        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;
        void update() noexcept final;
    };
}
