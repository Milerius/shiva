//
// Created by roman Sztergbaum on 23/06/2018.
//

#pragma once

#include <type_traits>
#include <sol/state.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/filesystem/filesystem.hpp>
#include <entt/core/utility.hpp>

namespace shiva::ecs::details
{
    template <typename SystemType>
    class lua_scripted_system : public system<lua_scripted_system<SystemType>, SystemType>
    {
    public:
        //! Public typedefs
        using TSystem = system <lua_scripted_system<SystemType>, SystemType>;

        //! Constructors
        inline lua_scripted_system(shiva::entt::dispatcher &dispatcher,
                                   shiva::entt::entity_registry &entity_registry,
                                   const float &fixed_delta_time,
                                   std::shared_ptr<sol::state> state,
                                   std::string table_name,
                                   std::string class_name) noexcept;

        //! Destructor
        inline ~lua_scripted_system() noexcept override;

        //! Callback
        template <typename EventType>
        void receive(const EventType &evt);

        //! Public member functions overriden
        inline void update() noexcept override;

        //! Reflection
        inline static const std::string &class_name() noexcept;

        inline static constexpr auto reflected_functions() noexcept;

        inline static constexpr auto reflected_members() noexcept;

    private:
        //! Private member functions
        template <typename EventType>
        void register_common_event_() noexcept;

        template <typename ... Types>
        void register_common_events_(meta::type_list<Types...>) noexcept;

        template <typename ... Args>
        void safe_function_(const std::string &function, Args &&... args) noexcept;

        //! Private data members
        std::shared_ptr<sol::state> state_;
        std::string table_name_;
        static inline std::string class_name_{""};
    };

    using lua_post_scripted_system = lua_scripted_system<shiva::ecs::system_post_update>;
    using lua_pre_scripted_system = lua_scripted_system<shiva::ecs::system_pre_update>;
    using lua_logic_scripted_system = lua_scripted_system<shiva::ecs::system_logic_update>;
}

namespace shiva::ecs::details
{
    //! Constructor
    template <typename SystemType>
    lua_scripted_system<SystemType>::lua_scripted_system(shiva::entt::dispatcher &dispatcher,
                                                         shiva::entt::entity_registry &entity_registry,
                                                         const float &fixed_delta_time,
                                                         std::shared_ptr<sol::state> state, std::string table_name,
                                                         std::string class_name) noexcept :
        TSystem::system(dispatcher, entity_registry, fixed_delta_time, class_name),
        state_(state),
        table_name_(std::move(table_name))
    {
      register_common_events_(shiva::event::common_events_list{});
      class_name_ = std::move(class_name);
      safe_function_("on_construct");
    }

    //! Destructor
    template <typename SystemType>
    lua_scripted_system<SystemType>::~lua_scripted_system() noexcept
    {
      safe_function_("on_destruct");
    }

    //! Callbacks
    template <typename SystemType>
    template <typename EventType>
    void lua_scripted_system<SystemType>::receive(const EventType &evt)
    {
      using namespace std::string_literals;
      this->log_->debug("event_type received: {}", EventType::class_name());
      safe_function_("on_"s + EventType::class_name(), evt);
    }

    //! Public member functions overriden
    template <typename SystemType>
    void lua_scripted_system<SystemType>::update() noexcept
    {
      safe_function_("update");
    }

    //! Reflection
    template <typename SystemType>
    const std::string &lua_scripted_system<SystemType>::class_name() noexcept
    {
      return class_name_;
    }

    template <typename SystemType>
    constexpr auto lua_scripted_system<SystemType>::reflected_functions() noexcept
    {
      return meta::makeMap();
    }

    template <typename SystemType>
    constexpr auto lua_scripted_system<SystemType>::reflected_members() noexcept
    {
      return meta::makeMap();
    }

    //! Private member functions
    template <typename SystemType>
    template <typename EventType>
    void lua_scripted_system<SystemType>::register_common_event_() noexcept
    {
     /* this->dispatcher_.template sink<EventType>().connect<::entt::overload<void(const EventType &evt)>(
          &lua_scripted_system<SystemType>::receive)>(this);*/
      this->log_->info("connect to event_type: {}", EventType::class_name());
    }

    template <typename SystemType>
    template <typename... Types>
    void lua_scripted_system<SystemType>::register_common_events_(meta::type_list<Types...>) noexcept
    {
      (register_common_event_<Types>(), ...);
    }

    template <typename SystemType>
    template <typename... Args>
    void lua_scripted_system<SystemType>::safe_function_(const std::string &function, Args &&... args) noexcept
    {
      try {
        sol::optional<sol::function> f = (*state_)[table_name_][function];
        if (f && f.value() != sol::lua_nil) {
          f.value()(std::forward<Args>(args)...);
        }
      }
      catch (const std::exception &error) {
        this->log_->error("lua error: [function: {0}, err: {1}]", function, error.what());
      }
    }
}
