//
// Created by roman Sztergbaum on 14/06/2018.
//

#pragma once

#include <shiva/ecs/system.hpp>
#include <shiva/event/quit_game.hpp>

namespace shiva::examples
{
    class pre_system : public shiva::ecs::post_update_system<pre_system>
    {
    public:
        reflect_class(pre_system);

        pre_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry, const float& fixed_delta_time) :
            system(dispatcher, registry, fixed_delta_time)
        {
        }

        void update() noexcept override
        {
            if (counter == 10) {
                this->dispatcher_.trigger<shiva::event::quit_game>(0);
            }
            std::cout << __FUNCTION__ << " name: "  << class_name() << std::endl;
            counter++;
        }

    private:
        size_t counter{0};
    };
}
