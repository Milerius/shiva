//
// Created by roman Sztergbaum on 24/08/2018.
//

#pragma once

#include <string>
#include <shiva/reflection/reflection.hpp>
#include <shiva/ecs/system_type.hpp>
#include <shiva/meta/list.hpp>

namespace shiva::event
{

    struct enable_system
    {
        enable_system() = default;

        using constructor_list_type_t = shiva::meta::type_list<std::string, shiva::ecs::system_type>;
        static constexpr const unsigned int nb_args = shiva::meta::list::Length<constructor_list_type_t>::value;

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