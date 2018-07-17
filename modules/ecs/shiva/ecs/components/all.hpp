//
// Created by roman Sztergbaum on 21/06/2018.
//

#pragma once

#include <shiva/meta/list.hpp>
#include <shiva/ecs/components/layer.hpp>
#include <shiva/ecs/components/drawable.hpp>

namespace shiva::ecs
{
    using common_components = meta::type_list<layer_1,
        layer_2,
        layer_3,
        layer_4,
        layer_5,
        layer_6,
        layer_7,
        layer_8,
        drawable>;
}