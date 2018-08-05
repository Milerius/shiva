//
// Created by roman Sztergbaum on 05/08/2018.
//

#pragma once

#include <array>
#if defined(fmt)
#undef fmt
#include <sol/state.hpp>
#else
#include <sol/state.hpp>
#endif
#include <shiva/spdlog/spdlog.hpp>

namespace shiva::lua
{
    template <typename T>
    void register_type(sol::state& state, shiva::logging::logger logger) noexcept
    {
        const auto table = std::tuple_cat(
            std::make_tuple(T::class_name()),
            T::reflected_functions(),
            T::reflected_members());

        try {
            std::apply(
                [&state](auto &&...params) {
                    state.new_usertype<T>(std::forward<decltype(params)>(params)...);
                }, table);
        }
        catch (const std::exception &error) {
            logger->error("error: {}", error.what());
            return;
        }

        logger->info("successfully registering type: {}", T::class_name());
    }
}
