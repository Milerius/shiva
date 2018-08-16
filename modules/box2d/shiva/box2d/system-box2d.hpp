//
// Created by roman Sztergbaum on 16/08/2018.
//

#pragma once

#include <Box2D/Box2D.h>
#include <shiva/ecs/system.hpp>

namespace shiva::plugins
{
    class box2d_system final : public shiva::ecs::logic_update_system<box2d_system>
    {
    public:
        //! Destructor
        ~box2d_system() noexcept final = default;

        //! Constructor
        box2d_system(shiva::entt::dispatcher &dispatcher,
                     shiva::entt::entity_registry &registry,
                     const float &fixed_delta_time) noexcept;

        //! Public static functions
        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;

        //! Public member function overriden
        void update() noexcept final;

        //! Reflection
        reflect_class(box2d_system)

        static constexpr auto reflected_functions() noexcept;

        static constexpr auto reflected_members() noexcept;
    private:
        b2World world_{{0.f, 0.f}};
    };
}