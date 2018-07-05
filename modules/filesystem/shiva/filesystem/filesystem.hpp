//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#if __has_include(<experimental/filesystem>) && !defined(__EMSCRIPTEN__)
    #include <experimental/filesystem>
    namespace shiva
    {
        namespace fs = std::experimental::filesystem;
    }
#elif __has_include(<filesystem>) && !defined(__EMSCRIPTEN__)
    #include <filesystem>
    namespace shiva
    {
      namespace fs = std::filesystem;
    }
#elif defined(__EMSCRIPTEN__)
    #include <boost/filesystem.hpp>
    namespace shiva
    {
      namespace fs = boost::filesystem;
    }
#endif