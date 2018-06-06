//
// Created by doom on 03/10/17.
//

#pragma once

#include <shiva/pp/pp_count_args.hpp>
#include <shiva/pp/pp_paste.hpp>
#include <shiva/pp/details/pp_for_each.hpp>

#define pp_for_each(fct, ...)                                               \
    __FOR_EACH_EXPAND(pp_paste(__FOR_EACH, pp_count_args(__VA_ARGS__))(fct, __VA_ARGS__))
