//
// Created by doom on 01/02/18.
//

#pragma once

#include <type_traits>

namespace meta
{
    namespace details
    {
        template <template <typename...> typename MetaFunction, typename, typename ...Params>
        struct is_detected : std::false_type
        {
        };

        template <template <typename...> typename MetaFunction, typename ...Params>
        struct is_detected<MetaFunction, std::void_t<MetaFunction<Params...>>, Params...> : std::true_type
        {
        };
    }

    template <template <typename...> typename MetaFunction, typename ...Params>
    using is_detected = details::is_detected<MetaFunction, void, Params...>;

    template <typename T, typename U>
    using comparison_t = decltype(std::declval<T &>() == std::declval<U &>());

    template <typename T, typename U>
    using is_eq_comparable_with = is_detected<comparison_t, T, U>;

    template <typename T, typename U>
    static constexpr const bool is_eq_comparable_with_v = is_eq_comparable_with<T, U>::value;
};
