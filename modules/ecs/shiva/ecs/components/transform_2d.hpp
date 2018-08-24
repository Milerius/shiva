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

        transform_2d(float x_,
                     float y_, float width_, float height_, float scale_x_, float scale_y_,
                     float angle_) noexcept :
            x(x_),
            y(y_),
            width(width_),
            height(height_),
            scale_x(scale_x_),
            scale_y(scale_y_),
            angle(angle_),
            original_x(x_)
        {
        }

        float x{0.0f}; //!< x
        float y{0.0f}; //!< y
        float width{0.0f};
        float height{0.0f};
        float scale_x{1.0f};
        float scale_y{1.0f};
        float angle{0.0f};
        bool rotating{false};

        //! Original (mutable because of EnTT, (should not be modified))
        mutable float original_x{x};
        mutable float original_y{y};
        mutable float original_width{width};
        mutable float original_height{height};

        reflect_class(transform_2d)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&transform_2d::y),
                                 reflect_member(&transform_2d::x),
                                 reflect_member(&transform_2d::width),
                                 reflect_member(&transform_2d::height),
                                 reflect_member(&transform_2d::scale_x),
                                 reflect_member(&transform_2d::scale_y),
                                 reflect_member(&transform_2d::angle),
                                 reflect_member(&transform_2d::rotating));
        }
    };
}