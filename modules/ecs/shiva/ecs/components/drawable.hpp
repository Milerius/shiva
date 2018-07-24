//
// Created by roman Sztergbaum on 17/07/2018.
//

#pragma once

#include <memory>

namespace shiva::ecs
{
    struct drawable
    {
        template <typename Drawable>
        drawable(Drawable ptr) noexcept : drawable_(ptr)
        {
        }

        reflect_class(drawable)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        std::shared_ptr<void> drawable_{nullptr};
    };
}