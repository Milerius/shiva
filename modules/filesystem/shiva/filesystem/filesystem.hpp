//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

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
