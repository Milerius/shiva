//
// Created by roman Sztergbaum on 23/06/2018.
//

#pragma once

#include <type_traits>
#include <sol/state.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/filesystem/filesystem.hpp>

namespace shiva::ecs
{
    template <typename SystemType>
    class lua_scripted_system : public system<lua_scripted_system<SystemType>, SystemType>
    {
    public:
        using TSystem = system<lua_scripted_system<SystemType>, SystemType>;

        lua_scripted_system(shiva::entt::dispatcher &dispatcher,
                        shiva::entt::entity_registry &entity_registry,
                        const float &fixed_delta_time,
                        std::shared_ptr<sol::state> state,
                        std::string table_name,
                        std::string class_name) noexcept :
            TSystem::system(dispatcher, entity_registry, fixed_delta_time),
            state_(state),
            table_name_(std::move(table_name))
        {
            class_name_ = std::move(class_name);
            safe_function("on_construct");
        }

        ~lua_scripted_system() noexcept override
        {
            safe_function("on_destruct");
        }

        void update() noexcept override
        {
            safe_function("update");
        }

        static const std::string &class_name() noexcept
        {
            return class_name_;
        }

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

    private:
        template <typename ... Args>
        void safe_function(const std::string &function, Args &&... args)
        {
            try {
                (*state_)[table_name_][function](std::forward<Args>(args)...);
            }
            catch (const std::exception &error) {
                std::cerr << error.what() << std::endl;
            }
        }

        std::shared_ptr<sol::state> state_;
        std::string table_name_;
        static inline std::string class_name_{""};
    };

    using post_scripted_system = lua_scripted_system<shiva::ecs::system_post_update>;
    using pre_scripted_system = lua_scripted_system<shiva::ecs::system_pre_update>;
    using logic_scripted_system = lua_scripted_system<shiva::ecs::system_logic_update>;
}
