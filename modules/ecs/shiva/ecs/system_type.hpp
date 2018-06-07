//
// Created by roman Sztergbaum on 04/06/2018.
//

#pragma once

#include <shiva/meta/named_type.hpp>

namespace shiva::ecs
{
    enum system_type
    {
        pre_update = 0,
        logic_update = 1,
        post_update = 2,
        size = 3,
    };

    using system_pre_update = fluent::NamedType<system_type, struct system_pre_update_tag>;
    using system_post_update = fluent::NamedType<system_type, struct system_post_update_tag>;
    using system_logic_update = fluent::NamedType<system_type, struct system_logic_update_tag>;
}
