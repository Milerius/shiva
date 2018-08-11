//
// Created by roman Sztergbaum on 01/06/2018.
//

#pragma once

#include <shiva/entt/entt.hpp>
#include <shiva/ecs/system_type.hpp>

namespace shiva::ecs
{
    /**
     * \class base_system
     * \note This class is an abstract class, it is documented but
     * is present only to make type-erasure of the class system which is templated.
     * \note This class can be manipulated when using plugins to share data between them.
     */
    class base_system
    {
    public:
        //! Constructors
        inline explicit base_system(entt::dispatcher &dispatcher,
                                    entt::entity_registry &entity_registry,
                                    const float &fixed_delta_time, bool im_plugin = false) noexcept;

        //! Destructor
        virtual ~base_system() noexcept = default;

        //! Pure virtual functions
        virtual void update() noexcept = 0;
        virtual const std::string &get_name() const noexcept = 0;
        virtual system_type get_system_type_RTTI() const noexcept = 0;

        //! virtual functions
        virtual void on_set_user_data() noexcept
        {}

        //! Public member functions

        /**
         * \note This function marks the system, it will be destroyed in the next turn of the game loop by the system_manager.
         */
        inline void mark() noexcept;

        /**
         * \note This function unmark the system, allows the prevention of a destruction in the next turn of the game loop by the system_manager.
         */
        inline void unmark() noexcept;

        /**
         * \note This function tell you if a system is marked or no.
         * \return true if the system is marked, false otherwise
         */
        inline bool is_marked() const noexcept;

        /**
         * \note This function enable a system.
         * \note by default a system is enabled.
         */
        inline void enable() noexcept;

        /**
         * \note This function disable a system.
         */
        inline void disable() noexcept;

        /**
         * \note This function tell you if a system is enable or no.
         */
        inline bool is_enabled() const noexcept;

        /**
         * \note This function defines the system as a plugin, and therefore will use more feature in runtime to work properly
         */
        inline void im_a_plugin() noexcept;

        /**
         * \note This function tell you if a system is a plugin or no
         * \return true if the system is a plugin, false otherwise
         */
        inline bool is_a_plugin() const noexcept;

        /**
         * \note This function retrieve a user data previously set by set_user_data
         * \note by default a user_data is a void pointer equal to nullptr.
         * \return user data of a system
         */
        inline void *get_user_data() noexcept;

        /**
         * \note This function set a user data for this system
         * \note This function is very usefull to transfer (with get_user_data) data between plugins since they are base_class.
         * \note This function will call on_set_user_data callback at the epilogue, by default on_set_user_data is empty and you need
         * to override it if you need it.
         * \note user should be aware here, that's manipulating void pointer is as your own risk.
         * \param data a void pointer representing the user data
         */
        inline void set_user_data(void *data) noexcept;

    protected:
        //! Protected data members
        [[maybe_unused]] entt::dispatcher &dispatcher_;
        [[maybe_unused]] entt::entity_registry &entity_registry_;
        [[maybe_unused]] const float &fixed_delta_time_;
        [[maybe_unused]] void *user_data_{nullptr};

    private:
        //! Private data members
        bool is_plugin{false};
        bool marked_{false};
        bool enabled_{true};
    };
}

namespace shiva::ecs
{
    //! Constructors
    base_system::base_system(entt::dispatcher &dispatcher, entt::entity_registry &entity_registry,
                             const float &fixed_delta_time, bool im_plugin) noexcept :
        dispatcher_(dispatcher),
        entity_registry_(entity_registry),
        fixed_delta_time_(fixed_delta_time),
        is_plugin{im_plugin}
    {
    }

    //! Public member functions
    void base_system::mark() noexcept
    {
        marked_ = true;
    }

    void base_system::unmark() noexcept
    {
        marked_ = false;
    }

    bool base_system::is_marked() const noexcept
    {
        return marked_;
    }

    void base_system::enable() noexcept
    {
        enabled_ = true;
    }

    void base_system::disable() noexcept
    {
        enabled_ = false;
    }

    bool base_system::is_enabled() const noexcept
    {
        return enabled_;
    }

    void base_system::im_a_plugin() noexcept
    {
        is_plugin = true;
    }

    bool base_system::is_a_plugin() const noexcept
    {
        return is_plugin;
    }

    void *base_system::get_user_data() noexcept
    {
        return user_data_;
    }

    void base_system::set_user_data(void *data) noexcept
    {
        user_data_ = data;
        on_set_user_data();
    }
}