//
// Created by roman Sztergbaum on 01/06/2018.
//

#pragma once

#include <shiva/ecs/using_alias_library.hpp>
#include <shiva/ecs/system_type.hpp>

namespace shiva::ecs
{
    class base_system
    {
    public:
        //! Constructors / Destructor
        explicit base_system(entt::dispatcher &dispatcher,
                             entt::entity_registry &entity_registry,
                             const float &fixed_delta_time, bool im_plugin = false) noexcept :
            dispatcher_(dispatcher),
            entity_registry_(entity_registry),
            fixed_delta_time_(fixed_delta_time),
            is_plugin{im_plugin}
        {
        }

        virtual ~base_system() noexcept = default;

        //! Pure virtual functions
        virtual void update() noexcept = 0;
        virtual const std::string &get_name() const noexcept = 0;
        virtual system_type get_system_type_RTTI() const noexcept = 0;
        virtual void on_set_user_data() noexcept
        {

        }

        //! Public member functions
        void mark() noexcept
        {
            marked_ = true;
        }

        void unmark() noexcept
        {
            marked_ = false;
        }

        bool is_marked() const noexcept
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

        bool is_enabled() const noexcept
        {
            return enabled_;
        }

        void im_a_plugin() noexcept
        {
            is_plugin = true;
        }

        bool is_a_plugin() const noexcept
        {
            return is_plugin;
        }

        void* get_user_data() noexcept
        {
            return user_data_;
        }

        void set_user_data(void *data) noexcept
        {
            user_data_ = data;
            on_set_user_data();
        }

    protected:
        [[maybe_unused]] entt::dispatcher &dispatcher_;
        [[maybe_unused]] entt::entity_registry &entity_registry_;
        [[maybe_unused]] const float &fixed_delta_time_;
        [[maybe_unused]] void *user_data_{nullptr};

    private:
        bool is_plugin{false};
        bool marked_{false};
        bool enabled_{true};
    };
}
