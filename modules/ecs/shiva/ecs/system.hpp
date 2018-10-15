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
     * \note This class is the class that you have to inherit to create your systems
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

        /**
         * \note this is the basic constructor
         * \tparam TArgs the arguments that are forwarded to the base_system constructor
         */
        template <typename ...TArgs>
        explicit system(TArgs &&...args) noexcept;

        /**
         * \note this constructor is used for scripting.
         * \param dispatcher represents a reference to the dispatcher, stored in base_system.
         * \param entity_registry represents a reference to the entity registry, stored in base system.
         * \param fixed_delta_time represents a reference to the fixed delta_time, stored in base_system.
         * \param class_name the name of the scripted class, used for logging.
         */
        inline system(shiva::entt::dispatcher &dispatcher,
                      shiva::entt::entity_registry &entity_registry,
                      const float &fixed_delta_time,
                      std::string class_name) noexcept;

        //! Destructors
        ~system() noexcept override;

        //! Public static functions

        /**
         * \note this function allows you to retrieve the type of a system at compile time.
         * \return ​system_type of the derived system.
         */
        static constexpr system_type get_system_type() noexcept;

        //! Pure virtual functions
        void update() noexcept override = 0;

        //! Public member functions overriden

        /**
         * \note this function allow you to get the name of the derived system
         * \return name of the derived system.
         */
        const std::string &get_name() const noexcept final;

        /**
         * \note this function allows you to retrieve the type of a system at runtime.
         * \return ​system_type of the derived system
         */
        system_type get_system_type_RTTI() const noexcept final;

    protected:
        //! Protected data members
        shiva::logging::logger log_;
    };

    /**
     * \typedef logic_update_system
     * \note this typedef is a shortcut, and this is the one that should be used when you want to inherit as a logical system.
     * \example
     * \code
     * class system_implementation : public logic_update_system<system_implementation>
     * {
     *
     * };
     * \endcode
     */
    template <typename TSystemDerived>
    using logic_update_system = system<TSystemDerived, system_logic_update>;


    /**
     * \typedef pre_update_system
     * \note this typedef is a shortcut, and this is the one that should be used when you want to inherit as a pre update system.
     * \code
     * class system_implementation : public pre_update_system<system_implementation>
     * {
     *
     * };
     * \endcode
     */
    template <typename TSystemDerived>
    using pre_update_system = system<TSystemDerived, system_pre_update>;

    /**
     * \typedef post_update_system
     * \note this typedef is a shortcut, and this is the one that should be used when you want to inherit as a post update system.
     * \code
     * class system_implementation : public post_update_system<system_implementation>
     * {
     *
     * };
     * \endcode
     */
    template <typename TSystemDerived>
    using post_update_system = system<TSystemDerived, system_post_update>;
}

namespace shiva::ecs
{
    //! Constructors
    template <typename TSystemDerived, typename TSystemType>
    template <typename... TArgs>
    system<TSystemDerived, TSystemType>::system(TArgs &&... args) noexcept : base_system(std::forward<TArgs>(args)...),
                                                                             log_{shiva::log::stdout_color_mt(
                                                                                 TSystemDerived::class_name())}
    {
        if (this->is_a_plugin()) {
#if defined(DEBUG)
            spdlog::set_level(spdlog::level::debug);
#endif
            spdlog::set_pattern("[%n][%r][pid: %P][%^%l%$]: %v");

            shiva::entt::details::init_library(entity_registry_, dispatcher_);
        }
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
        log_->debug("dropping {} logger", log_->name());
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
            return system_type::logic_update;
        } else if constexpr (std::is_same_v<TSystemType, system_pre_update>)
            return system_type::pre_update;
        else if constexpr (std::is_same_v<TSystemType, system_post_update>)
            return system_type::post_update;
        return system_type::size;
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

