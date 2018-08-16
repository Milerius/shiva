//
// Created by roman Sztergbaum on 16/08/2018.
//

#pragma once

#include <shiva/reflection/reflection.hpp>

namespace shiva::ecs
{
    struct lua_script
    {
        lua_script(std::string script_, std::string table_name_) noexcept :
            script(std::move(script_)), table_name(std::move(table_name_))
        {
        }

        lua_script() noexcept :
            script{""},
            table_name{""}
        {
        }

        reflect_class(lua_script)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap(reflect_member(&lua_script::script), reflect_member(&lua_script::table_name));
        }

        std::string script;
        std::string table_name;
    };
}