//
// Created by roman Sztergbaum on 13/06/2018.
//

#pragma once

#include <shiva/world/world.hpp>
#include <systems/all_systems.hpp>

namespace shiva::examples
{
    class my_world : public shiva::world
    {
    public:
        my_world()
        {
            system_manager_.load_systems<shiva::examples::post_system>();
            std::cout << "nb_systems: " << system_manager_.nb_systems() << std::endl;
        }
    private:
    };
}
