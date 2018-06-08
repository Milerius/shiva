//
// Created by roman Sztergbaum on 01/06/2018.
//

#pragma once

#include <shiva/ecs/using_alias_library.hpp>

namespace shiva::ecs
{
    class base_system
    {
    public:
        //! Constructors / Destructor
        explicit base_system(entt::dispatcher &dispatcher, entt::entity_registry& entity_registry) noexcept :
            dispatcher_(dispatcher),
            entity_registry_(entity_registry)
        {
        }

        virtual ~base_system() noexcept = default;

    public:
        //! Pure virtual functions
        virtual void update() noexcept = 0;
        virtual const std::string &get_name() const noexcept = 0;

        public:
        //! Public member functions
        void mark() noexcept
        {
            marked_ = true;
        }

        void unmark() noexcept
        {
            marked_ = false;
        }

        bool isMarked() const noexcept
        {
            return marked_;
        }

        void enable() noexcept
        {
            enabled_ = true;
        }

        void disable() noexcept
        {
            enabled_ = false;
        }

        bool isEnabled() const noexcept
        {
            return enabled_;
        }

    private:
        [[maybe_unused]] entt::dispatcher &dispatcher_;
        [[maybe_unused]] entt::entity_registry &entity_registry_;
        bool marked_{false};
        bool enabled_{false};
    };
}