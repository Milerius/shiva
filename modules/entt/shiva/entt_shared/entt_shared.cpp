//
// Created by roman Sztergbaum on 12/07/2018.
//

#include <shiva/entt_shared/entt_shared.hpp>
#include <shiva/event/all.hpp>


namespace shiva::entt_shared
{
    void init_library(shiva::entt::entity_registry &registry, shiva::entt::dispatcher &dispatcher)
    {
        init_events(dispatcher, shiva::event::common_events_list{});
    }
}