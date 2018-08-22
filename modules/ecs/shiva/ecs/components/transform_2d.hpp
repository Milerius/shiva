//
// Created by milerius on 22/08/18.
//

#pragma once

#include <shiva/reflection/reflection.hpp>

namespace shiva::ecs
{
    struct transform_2d
    {
        transform_2d() noexcept = default;

        transform_2d(float top_, float left_, float width_, float height_) noexcept :
            top(top_),
            left(left_),
            width(width_),
            height(height_)
        {
        }

        float top{0.0f};
        float left{0.0f};
        float width{0.0f};
        float height{0.0f};

        reflect_class(transform_2d);

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&transform_2d::top),
                                 reflect_member(&transform_2d::left),
                                 reflect_member(&transform_2d::width),
                                 reflect_member(&transform_2d::height));
        }
    };
}