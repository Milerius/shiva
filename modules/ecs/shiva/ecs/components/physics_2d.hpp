//
// Created by roman Sztergbaum on 23/08/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>
#include <shiva/enums/enums.hpp>

namespace shiva::ecs
{
    struct physics_2d
    {

        template <typename CPhysics>
        physics_2d(CPhysics ptr) noexcept : physics_(ptr)
        {
        }

        reflect_class(physics_2d)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        std::shared_ptr<void> physics_{nullptr};
    };
}
