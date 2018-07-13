//
// Created by roman Sztergbaum on 13/07/2018.
//

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <shiva/reflection/reflection.hpp>

namespace shiva::sfml::components
{
    struct sprite
    {
        template <typename ...Args>
        sprite(Args &&...args) noexcept : sprite_(std::forward<Args>(args)...)
        {
        }

        reflect_class(sprite);

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

        sf::Sprite sprite_;
    };
}
