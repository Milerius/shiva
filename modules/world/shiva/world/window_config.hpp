//
// Created by roman Sztergbaum on 30/08/2018.
//

#pragma once

#include <array>
#include <string>

namespace shiva
{
    struct windows_config
    {
        std::string name{"none"};
        std::array<unsigned int, 2> size{{1920, 1080}};
        bool vsync{false};
        bool fullscreen{false};
        bool native_resolution{false};
    };
}