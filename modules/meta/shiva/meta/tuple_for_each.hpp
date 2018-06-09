//
// Created by doom on 05/01/18.
//

#pragma once

#include <tuple>

namespace shiva::meta
{
    namespace details
    {
        template <typename Tuple, typename Fctor, size_t ...Indexes>
        void tuple_for_each_helper(Tuple &t, const Fctor &f, std::index_sequence<Indexes...>)
        {
            (f(std::get<Indexes>(t)), ...);
        }
    }

    template <typename ...Types, typename Fctor>
    void tuple_for_each(std::tuple<Types...> &t, const Fctor &f)
    {
        details::tuple_for_each_helper(t, f, std::index_sequence_for<Types...>{});
    }
}
