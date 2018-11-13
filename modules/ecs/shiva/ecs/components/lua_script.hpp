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
            script(script_.c_str()), table_name(table_name_.c_str())
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

        const char *script;
        const char *table_name;
    };
}