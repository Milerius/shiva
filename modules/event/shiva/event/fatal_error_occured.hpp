//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <system_error>

namespace shiva::event
{
    struct fatal_error_occured
    {
        fatal_error_occured(std::error_code ec) noexcept : ec_{std::move(ec)} // NOLINT
        {

        }

        reflect_class(fatal_error_occured)
        std::error_code ec_;
    };
}