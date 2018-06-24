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
    class scripted_system : public system<scripted_system<SystemType>, SystemType>
    {
    public:
        using TSystem = system <scripted_system<SystemType>, SystemType>;

        scripted_system(shiva::entt::dispatcher &dispatcher,
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
            try {
                (*state_)[table_name_]["on_construct"]();
            }
            catch (const std::exception &error) {
                std::cerr << error.what() << std::endl;
            }
        }

        ~scripted_system() noexcept override
        {
            try {
                (*state_)[table_name_]["on_destruct"]();
            }
            catch (const std::exception &error) {
                std::cerr << error.what() << std::endl;
            }
        }

        void update() noexcept override
        {
            try {
                (*state_)[table_name_]["update"]();
            }
            catch (const std::exception &error) {
                std::cerr << error.what() << std::endl;
            }
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
        std::shared_ptr<sol::state> state_;
        std::string table_name_;
        static inline std::string class_name_{""};
    };

    using post_scripted_system = scripted_system<shiva::ecs::system_post_update>;
    using pre_scripted_system = scripted_system<shiva::ecs::system_pre_update>;
    using logic_scripted_system = scripted_system<shiva::ecs::system_logic_update>;
}
