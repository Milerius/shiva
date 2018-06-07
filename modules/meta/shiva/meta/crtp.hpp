//
// Created by roman on 07/06/2018.
//

#pragma once

namespace fluent
{
    template<typename T, template<typename> class crtpType>
    struct crtp
    {
        T &underlying()
        { return static_cast<T &>(*this); }

        T const &underlying() const
        { return static_cast<T const &>(*this); }
    };

} // namespace fluent
