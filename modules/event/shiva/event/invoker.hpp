//
// Created by roman Sztergbaum on 25/08/2018.
//

#pragma once

#include <shiva/entt/entt.hpp>

namespace shiva::event
{
    template <typename Event, typename ...Arguments>
    struct invoker_dispatcher
    {
        constexpr invoker_dispatcher() noexcept = default;

        void operator()(shiva::entt::dispatcher &self, Arguments &&...args)
        {
            self.trigger<Event>(std::forward<Arguments>(args)...);
        }
    };
}