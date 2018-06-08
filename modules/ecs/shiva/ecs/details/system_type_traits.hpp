//
// Created by roman on 07/06/2018.
//

#pragma once

#include <type_traits>
#include <shiva/reflection/reflection.hpp>
#include <shiva/ecs/system_type.hpp>
#include <shiva/meta/list.hpp>

namespace shiva::ecs::details
{
    using plugin_system = struct plugin_system_tag;
    using no_plugin_system = struct no_plugin_system_tag;

    template<typename is_plugin>
    static constexpr bool is_plugged_system_v() noexcept
    {
        if constexpr (std::is_same_v<is_plugin, plugin_system>) {
            return true;
        } else
            return false;
    }

    using valid_systems_list = meta::TypeList<system_pre_update, system_logic_update, system_post_update>;

    template <typename ...types>
    static constexpr bool is_valid_system_v(meta::TypeList<types...>) noexcept
    {
        return std::disjunction_v<types ...>;
    }

    template <typename t_system>
    static constexpr bool is_system_v = std::is_base_of_v<base_system, t_system> &&
                                        refl::has_reflectible_class_name_v<t_system> &&
                                        t_system::get_system_type() < system_type::size;
}