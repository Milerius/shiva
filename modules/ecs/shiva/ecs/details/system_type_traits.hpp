//
// Created by roman on 07/06/2018.
//

#pragma once

#include <type_traits>
#include <shiva/ecs/base_system.hpp>
#include <shiva/reflection/reflection.hpp>
#include <shiva/ecs/system_type.hpp>
#include <shiva/meta/list.hpp>

namespace shiva::ecs::details
{
    using plugin_system = struct plugin_system_tag;
    using no_plugin_system = struct no_plugin_system_tag;

    template<typename IsPlugin>
    static constexpr bool is_plugged_system_v() noexcept
    {
        if constexpr (std::is_same_v<IsPlugin, plugin_system>) {
            return true;
        } else
            return false;
    }

    using valid_systems_list = meta::TypeList<system_pre_update, system_logic_update, system_post_update>;

    template <typename ...Types>
    static constexpr bool is_valid_system_v(meta::TypeList<Types...>) noexcept
    {
        return std::disjunction_v<Types ...>;
    }

    template <typename TSystem>
    static constexpr bool is_system_v = std::is_base_of_v<base_system, TSystem> &&
                                        refl::has_reflectible_class_name_v<TSystem> &&
                                        TSystem::get_system_type() < system_type::size;
}