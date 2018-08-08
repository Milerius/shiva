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
    /**
     * \class system
     * \tparam TSystemDerived CRTP implementation of the system
     * \tparam TSystemType Strong type representing the system_type of the implemented system
     * \inherit base_system
     * \note This class is the class you will have to inherit to create your systems
     */
    template <typename TSystemDerived, typename TSystemType>
    class system : public base_system
    {
    private:
        //! Private typedefs
        template <typename T>
        using is_kind_system = std::is_same<TSystemType, T>;
    public:
        //! Constructors
        template <typename ...Args>
        explicit system(Args &&...args) noexcept;

        system(shiva::entt::dispatcher &dispatcher,
               shiva::entt::entity_registry &entity_registry,
               const float &fixed_delta_time,
               std::string class_name) noexcept;

        //! Destructors
        ~system() noexcept override;

        //! Public static functions
        static constexpr system_type get_system_type() noexcept;

        //! Pure virtual functions
        void update() noexcept override = 0;

        //! Public member functions overriden
        const std::string &get_name() const noexcept final;

        system_type get_system_type_RTTI() const noexcept final;

    protected:
        //! Protected data members
        shiva::logging::logger log_;
    };

    template <typename TSystemDerived>
    using logic_update_system = system<TSystemDerived, system_logic_update>;

    template <typename TSystemDerived>
    using pre_update_system = system<TSystemDerived, system_pre_update>;

    template <typename TSystemDerived>
    using post_update_system = system<TSystemDerived, system_post_update>;
}

namespace shiva::ecs
{
    //! Constructors
    template <typename TSystemDerived, typename TSystemType>
    template <typename... Args>
    system<TSystemDerived, TSystemType>::system(Args &&... args) noexcept : base_system(std::forward<Args>(args)...),
                                                                           log_{shiva::log::stdout_color_mt(
                                                                               TSystemDerived::class_name())}
    {
        if (this->is_a_plugin())
            shiva::entt::init_library(entity_registry_, dispatcher_);
    }

    template <typename TSystemDerived, typename TSystemType>
    system<TSystemDerived, TSystemType>::system(shiva::entt::dispatcher &dispatcher,
                                               shiva::entt::entity_registry &entity_registry,
                                               const float &fixed_delta_time, std::string class_name) noexcept
        : base_system(dispatcher, entity_registry, fixed_delta_time),
          log_{shiva::log::stdout_color_mt(std::move(class_name))}
    {
    }

    //! Destructor
    template <typename TSystemDerived, typename TSystemType>
    system<TSystemDerived, TSystemType>::~system() noexcept
    {
        log_->info("dropping {} logger", log_->name());
        spdlog::drop(log_->name());
    }

    //! Public static functions
    template <typename TSystemDerived, typename TSystemType>
    constexpr system_type system<TSystemDerived, TSystemType>::get_system_type() noexcept
    {
        using is_same_list = meta::list::Transform<details::valid_systems_list, is_kind_system>;
        static_assert(details::is_valid_system_v(is_same_list{}),
                      "valid_system_list is an invalid template parameter");
        if constexpr (std::is_same_v<TSystemType, system_logic_update>) {
            return logic_update;
        } else if constexpr (std::is_same_v<TSystemType, system_pre_update>)
            return pre_update;
        else if constexpr (std::is_same_v<TSystemType, system_post_update>)
            return post_update;
        return size;
    }

    //! Public member functions overriden
    template <typename TSystemDerived, typename TSystemType>
    const std::string &system<TSystemDerived, TSystemType>::get_name() const noexcept
    {
        return TSystemDerived::class_name();
    }

    template <typename TSystemDerived, typename TSystemType>
    system_type system<TSystemDerived, TSystemType>::get_system_type_RTTI() const noexcept
    {
        return system::get_system_type();
    }
}

#define SYSTEM_BASIC_REFLECTION(name)                                                       \
    public:                                                                                 \
        reflect_class(name)                                                                 \
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

