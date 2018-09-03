//
// Created by roman Sztergbaum on 23/06/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>
#include <shiva/ecs/base_system.hpp>

namespace shiva::event
{
    struct add_base_system
    {
        add_base_system(std::unique_ptr<shiva::ecs::base_system> system_ptr_ = nullptr,
                        bool prioritize_ = false, std::string system_b = "") noexcept :
            system_ptr(std::move(system_ptr_)),
            prioritize(prioritize_),
            system_name(std::move(system_b))
        {
        }

        reflect_class(add_base_system)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        std::unique_ptr<shiva::ecs::base_system> system_ptr{nullptr};
        bool prioritize{false};
        std::string system_name;
    };
}
