//
// Created by avendel on 10.10.2018.
//

#pragma once

#include <cstdint>

namespace shiva::input::mouse {
    enum class Button : uint8_t {
        Left,
        Right,
        Middle,
        XButton1,
        XButton2,
        ButtonCount
    };

    enum class Wheel : uint8_t {
        VerticalWheel,
        HorizontalWheel
    };
}
