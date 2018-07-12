//
// Created by roman Sztergbaum on 12/07/2018.
//

#pragma once

#if defined(_WIN32)
    #define PP_API_EXPORT __declspec(dllexport)
    #define PP_API_IMPORT __declspec(dllimport)
    #ifdef _MSC_VER
            #pragma warning(disable: 4251)
    #endif
#else // Linux, FreeBSD, Mac OS X
    #if __GNUC__ >= 4
        #define PP_API_EXPORT __attribute__ ((__visibility__ ("default")))
        #define PP_API_IMPORT __attribute__ ((__visibility__ ("default")))
    #else
        #define PP_API_EXPORT
        #define PP_API_IMPORT
    #endif
#endif