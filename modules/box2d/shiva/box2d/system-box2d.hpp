//
// Created by roman Sztergbaum on 16/08/2018.
//

#pragma once

#include <Box2D/Box2D.h>
#include <shiva/lua/lua_helpers.hpp>
#include <shiva/ecs/system.hpp>

namespace shiva::plugins
{
    class box2d_system final : public shiva::ecs::logic_update_system<box2d_system>
    {
    public:
        class ContactListener final : public b2ContactListener
        {
        public:
            ContactListener(const shiva::entt::dispatcher &dispatcher) : dispatcher_(dispatcher)
            {
            }

        private:
            void BeginContact(b2Contact *contact) noexcept final
            {
                const auto first = contact->GetFixtureA()->GetBody()->GetUserData();
                const auto second = contact->GetFixtureB()->GetBody()->GetUserData();
                (void)dispatcher_;
                (void)first;
                (void)second;
            }

            const shiva::entt::dispatcher &dispatcher_;
        };

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
        //! Private member functions overriden
        void on_set_user_data_() noexcept final;

        ContactListener listener_;
        b2World world_{{0.f, 0.f}};
        sol::state* state_{nullptr};
    };
}