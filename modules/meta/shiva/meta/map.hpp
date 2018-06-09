//
// Created by doom on 25/11/17.
//

#pragma once

#include <tuple>
#include <shiva/meta/type_traits.hpp>

namespace shiva::meta
{
    template <typename ...Ts>
    using Map = std::tuple<Ts...>;

    namespace details
    {
        template <typename ...Ts, typename KeyT, typename FuncT>
        constexpr bool find(const Map<Ts...> &, KeyT &&, FuncT &&, std::index_sequence<>) noexcept
        {
            return false;
        }

        template <typename ...Ts, typename KeyT, typename FuncT, size_t I, size_t I2, size_t ...Is>
        constexpr bool find(const Map<Ts...> &map, KeyT &&needle, FuncT &&f, std::index_sequence<I, I2, Is...>) noexcept
        {
            using T1 = std::decay_t<decltype(std::get<I>(map))>;
            using T2 = std::decay_t<decltype(needle)>;

            if constexpr (shiva::meta::is_eq_comparable_with_v<T1, T2>) {
                if (std::get<I>(map) == needle) {
                    f(std::get<I>(map), std::get<I2>(map));
                    return true;
                }
            }
            return find(map, std::forward<KeyT>(needle), std::forward<FuncT>(f), std::index_sequence<Is...>{});
        }

        template <typename ...Ts, typename FuncT>
        constexpr void for_each(const Map<Ts...> &, const FuncT &, std::index_sequence<>) noexcept
        {
        }

        template <typename ...Ts, typename FuncT, size_t I, size_t I2, size_t ...Is>
        constexpr void for_each(const Map<Ts...> &map, const FuncT &f, std::index_sequence<I, I2, Is...>) noexcept
        {
            f(std::get<I>(map), std::get<I2>(map));
            for_each(map, f, std::index_sequence<Is...>{});
        }
    }

    template <typename ...Ts, typename KeyT, typename FuncT>
    constexpr auto find(const Map<Ts...> &map, KeyT &&needle, FuncT &&f) noexcept
    {
        return details::find(map, std::forward<KeyT>(needle), std::forward<FuncT>(f), std::index_sequence_for<Ts...>{});
    }

    template <typename ...Ts, typename FuncT>
    constexpr void for_each(const Map<Ts...> &map, const FuncT &f) noexcept
    {
        details::for_each(map, f, std::index_sequence_for<Ts...>{});
    }

    template <typename ...Ts>
    constexpr auto makeMap(Ts &&...ts) noexcept
    {
        return Map<Ts...>(std::forward<Ts>(ts)...);
    }
}