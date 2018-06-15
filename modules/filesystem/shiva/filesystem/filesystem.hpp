//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

/*#include <boost/filesystem.hpp>

namespace shiva
{
    namespace fs = boost::filesystem;
}*/

#if __has_include(<experimental/filesystem>)
    #include <experimental/filesystem>
    namespace shiva
    {
        namespace fs = std::experimental::filesystem;
    }
#elif __has_include(<filesystem>)
    #include <filesystem>
    namespace shiva
    {
      namespace fs = std::filesystem;
    }
#endif
