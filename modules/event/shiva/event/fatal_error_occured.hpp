//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <system_error>
#include <shiva/reflection/reflection.hpp>

namespace shiva::event
{
    struct fatal_error_occured
    {
        fatal_error_occured(std::error_code ec) noexcept : ec_{std::move(ec)} // NOLINT
        {
        }

        fatal_error_occured() noexcept : ec_{}
        {
        }

        reflect_class(fatal_error_occured)

        std::error_code ec_;
    };
}