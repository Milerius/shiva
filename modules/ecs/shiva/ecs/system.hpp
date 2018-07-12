//
// Created by roman Sztergbaum on 06/06/2018.
//

#pragma once

#include <shiva/spdlog/spdlog.hpp>
#include <shiva/ecs/base_system.hpp>
#include <shiva/ecs/details/system_type_traits.hpp>
#include <shiva/entt/entt_config.hpp>

namespace shiva::ecs
{
    template <typename SystemDerived, typename TSystemType>
    class system : public base_system
    {
        template <typename T>
        using is_kind_system = std::is_same<TSystemType, T>;
    public:
        template <typename ...Args>
        explicit system(Args &&...args) noexcept : base_system(std::forward<Args>(args)...),
                                                   log_{shiva::log::stdout_color_mt(SystemDerived::class_name())}
        {
            if (this->is_a_plugin())
                shiva::entt::init_library(entity_registry_, dispatcher_);
        }

        system(shiva::entt::dispatcher &dispatcher,
               shiva::entt::entity_registry &entity_registry,
               const float &fixed_delta_time,
               std::string class_name) noexcept : base_system(dispatcher, entity_registry, fixed_delta_time),
                                                  log_{shiva::log::stdout_color_mt(std::move(class_name))}
        {
        }

        ~system() noexcept override
        {
            log_->info("dropping {} logger", log_->name());
            spdlog::drop(log_->name());
        };

        static constexpr system_type get_system_type() noexcept
        {
            using is_same_list = meta::list::Transform<details::valid_systems_list, is_kind_system>;
            static_assert(details::is_valid_system_v(is_same_list{}),
                          "valid_system_list is an invalid template parameter");
            if constexpr (std::is_same_v<TSystemType, system_logic_update>)
                return logic_update;
            else if constexpr (std::is_same_v<TSystemType, system_pre_update>)
                return pre_update;
            else if constexpr (std::is_same_v<TSystemType, system_post_update>)
                return post_update;
            return size;
        }

        //! Override functions
        void update() noexcept override = 0;

        const std::string &get_name() const noexcept final
        {
            return SystemDerived::class_name();
        }

        system_type get_system_type_RTTI() const noexcept final
        {
            return system::get_system_type();
        }

    protected:
        shiva::logging::logger log_;
    };

    template <typename TSystemDerived>
    using logic_update_system = system<TSystemDerived, system_logic_update>;

    template <typename TSystemDerived>
    using pre_update_system = system<TSystemDerived, system_pre_update>;

    template <typename TSystemDerived>
    using post_update_system = system<TSystemDerived, system_post_update>;
}

#define SYSTEM_BASIC_REFLECTION(name)                                                       \
    public:                                                                                 \
        reflect_class(name);                                                                \
        static constexpr auto reflected_functions() noexcept                                \
        {                                                                                   \
            return shiva::meta::makeMap(reflect_function(&name::update));                   \
        }                                                                                   \
                                                                                            \
        static constexpr auto reflected_members() noexcept                                  \
        {                                                                                   \
            return shiva::meta::makeMap();                                                  \
        }                                                                                   \
private:                                                                                    \

//#define SYSTEM_COMPLETE_REFLECTION(name, ...)
