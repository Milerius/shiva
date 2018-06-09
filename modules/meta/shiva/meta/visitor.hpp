//
// Created by doom on 25/11/17.
//

#pragma once

#include <utility>

namespace shiva::meta
{
#ifdef _MSC_VER
    template <typename ...Funcs>
    class visitor : public Funcs...
    {
    public:
        constexpr explicit visitor(Funcs &&...funcs) noexcept : Funcs{std::forward<Funcs>(funcs)}...
        {
        }
    };
#else
    template <typename ...Funcs>
    class visitor : private Funcs...
    {
    public:
        constexpr explicit visitor(Funcs &&...funcs) noexcept : Funcs{std::forward<Funcs>(funcs)}...
        {
        }

        using Funcs::operator()...;
    };
#endif

    template <typename ...Funcs>
    auto makeVisitor(Funcs &&...funcs) noexcept
    {
        visitor<Funcs...> ret(std::forward<Funcs>(funcs)...);

        return ret;
    }
}