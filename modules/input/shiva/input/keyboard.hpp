//
// Created by roman Sztergbaum on 09/07/2018.
//

#pragma once

#include <shiva/enums/enums.hpp>

namespace shiva::input::keyboard
{
    ENUM(Key,
         A,
         B,
         C,
         D,
         E,
         F,
         G,
         H,
         I,
         J,
         K,
         L,
         M,
         N,
         O,
         P,
         Q,
         R,
         S,
         T,
         U,
         V,
         W,
         X,
         Y,
         Z,
         Num0,
         Num1,
         Num2,
         Num3,
         Num4,
         Num5,
         Num6,
         Num7,
         Num8,
         Num9,
         Escape,
         LControl,
         LShift,
         LAlt,
         LSystem,
         RControl,
         RShift,
         RAlt,
         RSystem,
         Menu,
         LBracket,
         RBracket,
         SemiColon,
         Comma,
         Period,
         Quote,
         Slash,
         BackSlash,
         Tilde,
         Equal,
         Dash,
         Space,
         Return,
         BackSpace,
         Tab,
         PageUp,
         PageDown,
         End,
         Home,
         Insert,
         Delete,
         Add,
         Subtract,
         Multiply,
         Divide,
         Left,
         Right,
         Up,
         Down,
         Numpad0,
         Numpad1,
         Numpad2,
         Numpad3,
         Numpad4,
         Numpad5,
         Numpad6,
         Numpad7,
         Numpad8,
         Numpad9,
         F1,
         F2,
         F3,
         F4,
         F5,
         F6,
         F7,
         F8,
         F9,
         F10,
         F11,
         F12,
         F13,
         F14,
         F15,
         Pause);

    using TKey = Key::EnumType;

    enum class Modifers : uint16_t {
        alt = 1 << 0,
        control = 1 << 1,
        shift = 1 << 2,
        system = 1 << 3
    };

    using T = std::underlying_type_t <Modifers>;

    inline Modifers operator | (Modifers lhs, Modifers rhs)
    {
        return (Modifers)(static_cast<T>(lhs) | static_cast<T>(rhs));
    }

    inline Modifers& operator |= (Modifers& lhs, Modifers rhs)
    {
        lhs = (Modifers)(static_cast<T>(lhs) | static_cast<T>(rhs));
        return lhs;
    }
}

#define __PAIRIFY_ELEM(v)         {pp_stringviewify(v), shiva::input::keyboard::Key::v},

#define MAGIC_INIT_LIST(...) {pp_for_each(__PAIRIFY_ELEM, __VA_ARGS__)}

#define KEYBOARD_INIT_LIST MAGIC_INIT_LIST(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,Num0,Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8,Num9,Escape,LControl,LShift,LAlt,LSystem,RControl,RShift,RAlt,RSystem,Menu,LBracket,RBracket,SemiColon,Comma,Period,Quote,Slash,BackSlash,Tilde,Equal,Dash,Space,Return,BackSpace,Tab,PageUp,PageDown,End,Home,Insert,Delete,Add,Subtract,Multiply,Divide,Left,Right,Up,Down,Numpad0,Numpad1,Numpad2,Numpad3,Numpad4,Numpad5,Numpad6,Numpad7,Numpad8,Numpad9,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,Pause)
