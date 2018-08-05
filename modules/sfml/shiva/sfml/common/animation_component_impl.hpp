//
// Created by roman Sztergbaum on 05/08/2018.
//

#pragma once

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

namespace shiva::sfml
{
    struct animation_component_impl
    {
        enum status
        {
            stopped,
            paused,
            playing
        };

        sf::Time delta;
        sf::Time elapsed;
        bool loop{false};   //! loop the animation
        int repeat{0}; //! repeat the animation x times.
        status current_status; //! status of the animation
        size_t current_frame;
        std::vector<sf::IntRect> frames;
    };
}
