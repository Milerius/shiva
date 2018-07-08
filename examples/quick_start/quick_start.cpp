//
// Created by roman Sztergbaum on 08/07/2018.
//

#include <shiva/world/world.hpp>

namespace my_game::systems
{
    class bar : public shiva::ecs::pre_update_system<bar>
    {
    public:
        bar(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
            const float &fixed_delta_time) :
            system(dispatcher, registry, fixed_delta_time)
        {
        }

        void update() noexcept final
        {
            std::cout << __FUNCTION__ << " name: " << class_name() << std::endl;
        }

        SYSTEM_BASIC_REFLECTION(bar)
    };

    class foo : public shiva::ecs::logic_update_system<foo>
    {
    public:
        foo(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
            const float &fixed_delta_time) :
            system(dispatcher, registry, fixed_delta_time)
        {
        }

        void update() noexcept final
        {
            std::cout << __FUNCTION__ << " name: " << class_name() << std::endl;
        }

        SYSTEM_BASIC_REFLECTION(foo)
    };

    class folk : public shiva::ecs::post_update_system<folk>
    {
    public:
        folk(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
             const float &fixed_delta_time) :
            system(dispatcher, registry, fixed_delta_time)
        {
        }

        void update() noexcept final
        {
            if (counter == 10) {
                this->dispatcher_.trigger<shiva::event::quit_game>(0);
            }
            std::cout << __FUNCTION__ << " system: " << class_name() << std::endl;
            counter++;
        }

        SYSTEM_BASIC_REFLECTION(folk)
    private:
        size_t counter{0};
    };
}

namespace my_game
{
    class my_world : public shiva::world
    {
    public:
        my_world()
        {
            system_manager_.load_systems<my_game::systems::foo, my_game::systems::bar, my_game::systems::folk>();
        }

    private:
    };
}

int main()
{
    my_game::my_world world;
    return world.run();
}