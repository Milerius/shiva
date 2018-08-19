//
// Created by roman Sztergbaum on 19/08/2018.
//

#pragma once

#include <shiva/lua/lua_helpers.hpp>
#include <shiva/enums/enums.hpp>
#include <string>

namespace shiva::sfml
{
    struct video_component_impl
    {
        ENUM(status,
             stopped, //!< animation is stopped
             paused,  //!< animation is paused
             playing) //!< animation is playing

        std::string title;
        status current_status;
        bool status_change{false};
        sol::function functor{sol::lua_nil};
    };
}
