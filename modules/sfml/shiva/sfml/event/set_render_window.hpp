//
// Created by roman Sztergbaum on 18/06/2018.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace shiva::sfml::event
{
    struct set_render_window
    {
        set_render_window(sf::RenderWindow &win_) noexcept : win(&win_)
        {
        }

        sf::RenderWindow *win;
    };
}
