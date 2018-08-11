//
// Created by roman Sztergbaum on 11/08/2018.
//

#pragma once

#include <system_error>

namespace shiva::error
{
    enum class code
    {
        get_system_error = 27,
    };
}

namespace std
{
    template <>
    struct is_error_code_enum<shiva::error::code> : true_type {};
}

std::error_code make_error_code(shiva::error::code);

