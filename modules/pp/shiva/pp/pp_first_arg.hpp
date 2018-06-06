//
// Created by doom on 03/10/17.
//

#pragma once

#ifdef _MSC_VER
#define __FIRST_ARG_(f, ...)    f
#define __FIRST_ARG(args)       __FIRST_ARG_ args
#define pp_first_arg(...)       __FIRST_ARG((__VA_ARGS__))
#else
#define pp_first_arg(f, ...)    f
#endif