//
// Created by roman Sztergbaum on 24/08/2018.
//

#pragma once

#include <string>
#include <shiva/reflection/reflection.hpp>
#include <shiva/ecs/system_type.hpp>
#include <shiva/event/invoker.hpp>

namespace shiva::event
{

    struct enable_system
    {
        enable_system() = default;

        static constexpr const shiva::event::invoker_dispatcher<enable_system, std::string, shiva::ecs::system_type> invoker{};

        enable_system(std::string system_name_, shiva::ecs::system_type sys_type_) noexcept :
            system_name(std::move(system_name_)),
            sys_type(sys_type_)
        {
        }

        reflect_class(enable_system)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        std::string system_name{""};
        shiva::ecs::system_type sys_type{shiva::ecs::system_type::size};
    };
}