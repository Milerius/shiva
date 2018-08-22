//
// Created by roman Sztergbaum on 16/08/2018.
//

#pragma once

#include <Box2D/Box2D.h>

namespace shiva::box2d
{
    struct box2d_component
    {
        ~box2d_component() noexcept
        {
            if (body != nullptr) {
                body->GetWorld()->DestroyBody(body);
            }
        }

        b2Body *body{nullptr};
    };
}
