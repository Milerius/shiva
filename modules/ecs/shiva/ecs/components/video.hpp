//
// Created by roman Sztergbaum on 19/08/2018.
//

#pragma once

#include <memory>
#include <shiva/reflection/reflection.hpp>

namespace shiva::ecs
{
    struct video
    {
        template <typename Video>
        video(Video ptr) noexcept : video_(ptr)
        {
        }

        reflect_class(video)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        std::shared_ptr<void> video_{nullptr};
    };
}