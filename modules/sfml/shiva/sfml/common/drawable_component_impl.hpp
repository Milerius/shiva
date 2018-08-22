//
// Created by milerius on 22/08/18.
//

#pragma once

#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace shiva::sfml
{
    struct drawable_component_impl
    {
        drawable_component_impl() noexcept = default;

        template <typename Concrete>
        drawable_component_impl(Concrete ptr,
                                std::shared_ptr<sf::Drawable> drawable_,
                                std::shared_ptr<sf::Transformable> transformable_) noexcept :
            concrete(ptr),
            drawable(drawable_),
            transformable(transformable_)
        {
        }

        std::shared_ptr<void> concrete{nullptr};
        std::shared_ptr<sf::Drawable> drawable{nullptr};
        std::shared_ptr<sf::Transformable> transformable{nullptr};
    };
}