//
// Created by roman Sztergbaum on 05/08/2018.
//

#pragma once

#include <memory>
#include <shiva/reflection/reflection.hpp>

namespace shiva::ecs
{
    struct animation
    {
        template <typename Animation>
        animation(Animation ptr) noexcept : animation_(ptr)
        {
        }

        reflect_class(animation)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        std::shared_ptr<void> animation_{nullptr};
    };
}