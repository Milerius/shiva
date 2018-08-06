//
// Created by roman Sztergbaum on 06/08/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>

namespace shiva::event
{
    struct change_scene
    {
        using constructor_arg_type_t = const char*;

        reflect_class(change_scene)

        change_scene(const char* scene_name_ = nullptr) noexcept : scene_name(scene_name_)
        {
        }

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&change_scene::scene_name));
        }

        const char* scene_name{nullptr};
    };
}