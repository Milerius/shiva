//
// Created by roman Sztergbaum on 15/06/2018.
//

#include <gtest/gtest.h>
#include <shiva/enums/enums.hpp>

namespace
{
    ENUM(AnEnum, VALUE_A, VALUE_B);
}

TEST(enums, size)
{
    ASSERT_EQ(sizeof(AnEnum), sizeof(int)); //enums default to int
}

TEST(enums, creation)
{

    AnEnum v(AnEnum::VALUE_A);
    ASSERT_EQ(v, AnEnum::VALUE_A);

    v = AnEnum::VALUE_B;
    ASSERT_EQ(v, AnEnum::VALUE_B);

    ASSERT_EQ(v.toString(), "VALUE_B");

    AnEnum s("VALUE_A");
    ASSERT_EQ(s, AnEnum::VALUE_A);

    s = "VALUE_B";
    ASSERT_EQ(s, AnEnum::VALUE_B);
}

TEST(enums, invalid_conversion)
{
    ASSERT_THROW(AnEnum lala("lala"), AnEnum::InvalidConversion);

    ASSERT_EQ(AnEnum::size(), 2u);
}

TEST(enums, loop)
{
    size_t i = 0;

    for (const auto &cur : AnEnum::values()) {
        if (i++ == 0) {
            ASSERT_EQ(cur, AnEnum::VALUE_A);
        } else {
            ASSERT_EQ(cur, AnEnum::VALUE_B);
        }
    }
}

TEST(enums, lazy_conversion)
{
    std::string s = "lala" + AnEnum::toString(AnEnum::VALUE_B) + "lulu";

    ASSERT_EQ(s, "lalaVALUE_Blulu");
}

namespace
{
    ENUM(KeyCode,
        a, b, c, d, e,
        f, g, h, i, j,
        k, l, m, n, o,
        p, q, r, s, t,
        u, v, w, x, y,
        z,

        A, B, C, D, E,
        F, G, H, I, J,
        K, L, M, N, O,
        P, Q, R, S, T,
        U, V, W, X, Y,
        Z,

        _0, _1, _2, _3, _4,
        _5, _6, _7, _8, _9,

        F1, F2, F3, F4, F5, F6,
        F7, F8, F9, F10, F11, F12,

        Escape,

        Tab, CapsLock, Shift, Ctrl,
        Fn, Home, Alt, Space, AltGr,
        Left, Right, Up, Down
    );
}

TEST(enums, big)
{
    ASSERT_EQ(KeyCode::toString(KeyCode::Down), "Down");
}