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
            stopped, //!< animation is stopped
            paused, //!< animation is paused
            playing //!< animation is playing.
        };

        sf::Time delta; //!< delta time
        sf::Time elapsed; //!< time elasped since last frame
        bool loop{false};   //!< loop the animation
        int repeat{0}; //!< repeat the animation x times.
        status current_status; //!< status of the animation
        size_t current_frame; //!< current frame of the animation
        std::vector<sf::IntRect> frames; //!< array of frames.
    };
}
