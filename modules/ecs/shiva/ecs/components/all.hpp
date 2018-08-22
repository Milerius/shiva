//
// Created by roman Sztergbaum on 21/06/2018.
//

#pragma once

#include <shiva/meta/list.hpp>
#include <shiva/ecs/components/layer.hpp>
#include <shiva/ecs/components/drawable.hpp>
#include <shiva/ecs/components/animation.hpp>
#include <shiva/ecs/components/lua_script.hpp>
#include <shiva/ecs/components/video.hpp>
#include <shiva/ecs/components/transform_2d.hpp>

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
        drawable,
        animation,
        lua_script,
        video,
        transform_2d>;
}