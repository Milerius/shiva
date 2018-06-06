//
// Created by doom on 18/11/17.
//

#pragma once

namespace meta
{
    /**
     * Priority tag class, to control overloading fallbacks.
     */
    template <unsigned int Level>
    struct priority_tag : public priority_tag<Level - 1>
    {
    };

    template <>
    struct priority_tag<0>
    {
    };
}