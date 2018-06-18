//
// Created by roman Sztergbaum on 18/06/2018.
//

#pragma once

#include <chrono>

namespace shiva::timer
{
    using namespace std::chrono_literals;

    constexpr std::chrono::nanoseconds _60fps{16666666ns};
    constexpr std::chrono::nanoseconds _120fps{8333333ns};
    constexpr std::chrono::nanoseconds _144fps{6944444ns};
}
