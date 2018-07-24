//
// Created by roman Sztergbaum on 13/06/2018.
//

#pragma once

#include <iostream>

namespace shiva::examples
{
    class post_system : public shiva::ecs::post_update_system<post_system>
    {
    public:
        post_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                    const float &fixed_delta_time) :
            system(dispatcher, registry, fixed_delta_time)
        {
        }

        void update() noexcept override
        {
            if (counter == 10) {
                this->dispatcher_.trigger<shiva::event::quit_game>(0);
            }
            std::cout << __FUNCTION__ << " name: " << class_name() << std::endl;
            counter++;
        }

    public:
        reflect_class(post_system)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap(reflect_function(&post_system::update));
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

    private:
        size_t counter{0};
    };
}