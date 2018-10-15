//
// Created by roman Sztergbaum on 04/06/2018.
//

#pragma once

#include <chrono>

#include <shiva/meta/named_type.hpp>

namespace shiva::ecs
{
    /**
     * \enum system_type
     * \note Shiva have 3 different kinds of systems:
     * \note - PreUpdate: These systems are the first to be updated in the game loop,
     * they are generally used to retrieve user input, or manage network events for example.
     * \note - LogicUpdate: These systems are the second to be updated in the game loop,
     * they are generally used for game logic such as movement or collisions for example.
     * \note - PostUpdate: These systems are the last to be updated in the game loop,
     * they are generally used for rendering or interpolation for example.
     */
    enum system_type : uint8_t
    {
        pre_update = 0,
        logic_update = 1,
        post_update = 2,
        size,
    };

    /**
     * \typedef strong type of system_type::pre_update
     */
    using system_pre_update = fluent::NamedType<system_type, struct system_pre_update_tag>;


    /**
     * \typedef strong type of system_type::post_update
     */
    using system_post_update = fluent::NamedType<system_type, struct system_post_update_tag>;


    /**
     * \typedef strong type of system_type::logic_update
     */
    using system_logic_update = fluent::NamedType<system_type, struct system_logic_update_tag>;

    using delta_t = std::chrono::duration<float>;
}
