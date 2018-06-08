//
// Created by roman Sztergbaum on 27/05/2018.
//

#pragma once

#include <shiva/ecs/system_manager.hpp>
#include <shiva/error/general_error_handler.hpp>

namespace shiva
{
    class world
    {
    public:
        world()
        {

        }

    protected:
        shiva::entt::dispatcher dispatcher_;
        shiva::entt::entity_registry entity_registry_;
        shiva::error::general_handler error_handler{dispatcher_, entity_registry_};
        shiva::ecs::system_manager system_manager_{dispatcher_, entity_registry_};
    };
}