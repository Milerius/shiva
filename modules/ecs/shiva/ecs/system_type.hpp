//
// Created by roman Sztergbaum on 04/06/2018.
//

#pragma once

namespace shiva::ecs
{
    enum system_type
    {
        pre_update = 0,
        logic_update = 1,
        post_update = 2,
        size = 3,
    };
}
