//
// Created by roman Sztergbaum on 31/05/2018.
//

#pragma once

#include <memory>
#include <shiva/range/range.hpp>
#include <shiva/error/expected.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/ecs/system_type.hpp>
#include <shiva/event/fatal_error_occured.hpp>
#include <shiva/event/quit_game.hpp>
#include <shiva/event/start_game.hpp>
#include <shiva/event/after_load_systems_plugins.hpp>
#include <shiva/event/add_base_system.hpp>
#include <shiva/event/enable_system.hpp>
#include <shiva/event/disable_system.hpp>
#include <shiva/dll/plugins_registry.hpp>
#include <shiva/timer/timestep.hpp>
#include <shiva/spdlog/spdlog.hpp>

namespace shiva::ecs
{
    /**
     * \note This class manage the systems of the entity component system.
     * \note You are able to add, remove, retrieve , update or delete systems through it.
     * \class system_manager
     */
    class system_manager
    {
    public:
        //! Public typedefs
        using system_ptr = std::unique_ptr<base_system>;
        using system_array = std::vector<system_ptr>;
        using system_registry = std::array<system_array, system_type::size>;
        typedef system_ptr (pluginapi_create_t)(shiva::entt::dispatcher &, shiva::entt::entity_registry &,
                                                const float &fixed_delta_time);
        using plugins_registry_t = shiva::helpers::plugins_registry<pluginapi_create_t>;

        //! Public callbacks

        /**
         * \note this callback is called if the event quit_game is triggered by the program.
         * \warning the event content is unused.
         * \param evt the current event
         */
        inline void receive(const shiva::event::quit_game &evt);

        /**
         * \note this callback is called if the event start_game is triggered by the program.
         * \warning the event content is unused.
         * \param evt the current event
         */
        inline void receive(const shiva::event::start_game &evt);

        /**
         * \note this callback is called if the event add_base_system is triggered by the program.
         * \note internally, the content of the event which is a system will be added to the system manager.
         * \param evt the current event
         */
        inline void receive(const shiva::event::add_base_system &evt);

        /**
         * \note this callback is called if the event enable_system is triggered by the program.
         * \note internally, the content of the event which is a string will be used to retrieve the system and enable it.
         * \param evt the current event
         */
        inline void receive(const shiva::event::enable_system &evt);

        /**
         * \note this callback is called if the event disable_system is triggered by the program.
         * \note internally, the content of the event which is a string will be used to retrieve the system and disable it.
         * \param evt the current event
         */
        inline void receive(const shiva::event::disable_system &evt);

        //! Constructors

        /**
         * \note Basic constructor
         * \param dispatcher The dispatcher is provided to the system when it is created.
         * \param registry The entity_registry is provided to the system when it is created.
         * \param plugins_registry registry of the plugged systems
         * \see plugins_registry
         */
        inline explicit system_manager(entt::dispatcher &dispatcher,
                                       entt::entity_registry &registry,
                                       plugins_registry_t &plugins_registry) noexcept;

        //! Public member functions
        inline bool prioritize_system(const std::string &system_to_swap, const std::string &system_b,
                                      shiva::ecs::system_type sys_type) noexcept;

        /**
         * \return number of systems successfully updated
         * \note This is the function that update your systems.
         * \note Based on the logic of the different kinds of shiva systems,
         * this function take care of updating your systems in the right order.
         * \warning If you have not loaded any system into the system_manager the function return 0.
         * \warning If you decide to mark a system, it's automatically deleted at the next loop tick through this function.
         */
        inline size_t update() noexcept;

        inline size_t update_systems(shiva::ecs::system_type system_type_to_update) noexcept;

        /**
         * \note This function allow you to get a system through a template parameter.
         * \tparam TSystem represents the system to get.
         * \return A reference to the system obtained.
         */
        template <typename TSystem>
        const TSystem &get_system() const noexcept;

        /**
         * \overload get_system
         */
        template <typename TSystem>
        TSystem &get_system() noexcept;

        /**
         * \note This function allow you to get multiple system through multiple templates parameters.
         * \tparam TSystems represents a list of systems to get
         * \return Tuple of systems obtained.
         * \details This function recursively calls the get_system function
         * \see get_system
         */
        template <typename ...TSystems>
        std::tuple<std::add_lvalue_reference_t<TSystems>...> get_systems() noexcept;

        /**
         * @overload get_systems
         */
        template <typename ...TSystems>
        std::tuple<std::add_lvalue_reference_t<std::add_const_t<TSystems>>...> get_systems() const noexcept;

        /**
         * \note This function allow you to verify if a system is already registered in the system_manager.
         * \tparam TSystem Represents the system that needs to be verified
         * \return true if the system has been loaded, false otherwise
         */
        template <typename TSystem>
        bool has_system() const noexcept;

        /**
         * \note This function allow you to verify if a list of systems is already registered in the system_manager.
         * \tparam TSystems represents a list of system that needs to be verified
         * \return true if the list of systems has been loaded, false otherwise
         * \details This function recursively calls the has_system function
         * \see has_system
         */
        template <typename ... TSystems>
        bool has_systems() const noexcept;

        /**
         * \note This function marks a system that will be destroyed at the next tick of the game loop.
         * \tparam TSystem Represents the system that needs to be marked
         * \return true if the system has been marked, false otherwise
         */
        template <typename TSystem>
        bool mark_system() noexcept;

        /**
         * \note This function marks a list of systems, marked systems will be destroyed at the next tick of the game loop.
         * \tparam TSystems Represents a list of systems that needs to be marked
         * \return true if  the list of systems has been marked, false otherwise
         * \details This function recursively calls the mark_system function
         * \see mark_system
         */
        template <typename ... TSystems>
        bool mark_systems() noexcept;

        /**
         * \note This function enable a system
         * \tparam TSystem Represents the system that needs to be enabled.
         * \return true if the system has been enabled, false otherwise
         */
        template <typename TSystem>
        bool enable_system() noexcept;

        /**
         * \note This function enable a list of systems
         * \tparam TSystems Represents a list of systems that needs to be enabled
         * \return true if the list of systems has been enabled, false otherwise
         * \details This function recursively calls the enable_system function
         * \see enable_system
         */
        template <typename ... TSystems>
        bool enable_systems() noexcept;

        /**
         * \note This function disable a system
         * \tparam TSystem Represents the system that needs to be disabled
         * \return true if the the system has been disabled, false otherwise
         * \attention If you deactivate a system, it will not be destroyed but simply ignore during the game loop
         */
        template <typename TSystem>
        bool disable_system() noexcept;

        /**
         * \note This function disable a list of systems
         * \tparam TSystems  Represents a list of systems that needs to be disabled
         * \return true if the list of systems has been disabled, false otherwise
         * \details This function recursively calls the disable_system function
         */
        template <typename ... TSystems>
        bool disable_systems() noexcept;

        /**
         * \note This function allow you to create a system with the given argument
         * \note This function is a factory
         * \tparam TSystem represents the type of system to create
         * \tparam TSystemArgs represents the arguments needed to construct the system to create
         * \return Returns a reference to the created system
         */
        template <typename TSystem, typename ... TSystemArgs>
        TSystem &create_system(TSystemArgs &&...args) noexcept;

        /**
         * \tparam TSystems represents a list of systems to be loaded
         * \return Tuple of systems loaded
         * \see create_system
         */
        template <typename ...TSystems, typename ...TArgs>
        auto load_systems(TArgs &&...args) noexcept;

        /**
         * \return number of systems
         */
        inline size_t nb_systems() const noexcept;

        /**
         * \param sys_type represent the type of systems.
         * \return number of systems of a specific type.
         */
        inline size_t nb_systems(system_type sys_type) const noexcept;

        /**
         * \note This function allow you to load the plugins of the plugins_registry and create systems
         * with the creator functions of each plugins.
         * \return true if all the plugins has been successfully loaded, false otherwise
         */
        inline bool load_plugins() noexcept;
        inline bool hot_reload_plugins() noexcept;

        /**
         * \note This function allow you to get a system by his name, used for get a specific plugin for example.
         * \param system_name name of the system to get
         * \param type system_type of the system to get
         * \return a pointer to the base system which match this name, nullptr otherwise.
         */
        inline const base_system *get_system_by_name(std::string system_name,
                                                     shiva::ecs::system_type type) const noexcept;

        /**
         * \overload get_system_by_name
         */
        inline base_system *get_system_by_name(std::string system_name, shiva::ecs::system_type type) noexcept;

    private:
        //! Private member functions
        inline base_system &add_system_(system_ptr &&system, system_type sys_type) noexcept;

        template <typename TSystem>
        tl::expected<std::reference_wrapper<TSystem>, std::error_code> get_system_() noexcept;

        template <typename TSystem>
        tl::expected<std::reference_wrapper<const TSystem>, std::error_code> get_system_() const noexcept;

        inline void sweep_systems_() noexcept;

        //! Private data members
        using clock = std::chrono::steady_clock;
        clock::time_point start_{clock::now()};
        shiva::timer::time_step timestep_;
        entt::dispatcher &dispatcher_;
        entt::entity_registry &ett_registry_;
        plugins_registry_t &plugins_registry_;
        system_registry systems_{{}};
        bool need_to_sweep_systems_{false};
        std::shared_ptr<spdlog::logger> log_{shiva::log::stdout_color_mt("system_manager")};
    };
}

//! system_manager implementation
namespace shiva::ecs
{
    //! Public callbacks
    void system_manager::receive([[maybe_unused]] const shiva::event::quit_game &evt)
    {
        log_->debug("quit_game event received");
        shiva::ranges::for_each(systems_, [](auto &&vec) {
            shiva::ranges::for_each(vec, [](auto &&sys) {
                sys->disable();
            });
        });
    }

    void system_manager::receive([[maybe_unused]] const shiva::event::start_game &evt)
    {
        timestep_.start();
        start_ = clock::now();
    }

    void system_manager::receive(const shiva::event::add_base_system &evt)
    {
        auto sys_type = evt.system_ptr->get_system_type_RTTI();
        [[maybe_unused]] auto &system = add_system_(
            std::move(const_cast<shiva::event::add_base_system &>(evt).system_ptr),
            sys_type);
        if (evt.prioritize) {
            prioritize_system(system.get_name(), evt.system_name, sys_type);
        }
    }

    void system_manager::receive(const shiva::event::enable_system &evt)
    {
        auto system_ptr = this->get_system_by_name(evt.system_name, evt.sys_type);
        if (system_ptr)
            system_ptr->enable();
    }

    void system_manager::receive(const shiva::event::disable_system &evt)
    {
        auto system_ptr = this->get_system_by_name(evt.system_name, evt.sys_type);
        if (system_ptr)
            system_ptr->disable();
    }

    //! Constructor
    system_manager::system_manager(entt::dispatcher &dispatcher, entt::entity_registry &registry,
                                   system_manager::plugins_registry_t &plugins_registry) noexcept :
        dispatcher_(dispatcher),
        ett_registry_(registry),
        plugins_registry_(plugins_registry)
    {
        dispatcher_.sink<shiva::event::start_game>().connect(this);
        dispatcher_.sink<shiva::event::quit_game>().connect(this);
        dispatcher_.sink<shiva::event::add_base_system>().connect(this);
        dispatcher_.sink<shiva::event::enable_system>().connect(this);
        dispatcher_.sink<shiva::event::disable_system>().connect(this);
        log_->info("system_manager successfully created");
    }

    //! Public member functions
    size_t system_manager::update() noexcept
    {
        if (!nb_systems())
            return 0u;

        size_t nb_systems_updated = 0u;
        timestep_.start_frame();
        nb_systems_updated += update_systems(shiva::ecs::system_type::pre_update);

        while (timestep_.is_update_required()) {
            nb_systems_updated += update_systems(shiva::ecs::system_type::logic_update);
            timestep_.perform_update();
        }

        nb_systems_updated += update_systems(shiva::ecs::system_type::post_update);

        if (need_to_sweep_systems_) {
            sweep_systems_();
        }

        auto end = clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start_;
        if (elapsed_seconds.count() > 5) {
            this->hot_reload_plugins();
            start_ = clock::now();
        }

        return nb_systems_updated;
    }

    template <typename TSystem>
    const TSystem &system_manager::get_system() const noexcept
    {
        const auto ret = get_system_<TSystem>().or_else([this](const std::error_code &ec) {
            this->dispatcher_.trigger<shiva::event::fatal_error_occured>(ec);
        });
        return (*ret).get();
    }

    template <typename TSystem>
    TSystem &system_manager::get_system() noexcept
    {
        auto ret = get_system_<TSystem>().or_else([this](const std::error_code &ec) {
            this->dispatcher_.trigger<shiva::event::fatal_error_occured>(ec);
        });
        return (*ret).get();
    }

    template <typename... TSystems>
    std::tuple<std::add_lvalue_reference_t<TSystems>...> system_manager::get_systems() noexcept
    {
        return {get_system<TSystems>()...};
    }

    template <typename... TSystems>
    std::tuple<std::add_lvalue_reference_t<std::add_const_t<TSystems>>...> system_manager::get_systems() const noexcept
    {
        return {get_system<TSystems>()...};
    }

    template <typename TSystem>
    bool system_manager::has_system() const noexcept
    {
        static_assert(details::is_system_v<TSystem>,
                      "The system type given as template parameter doesn't seems to be valid");
        constexpr const auto sys_type = TSystem::get_system_type();
        return shiva::ranges::any_of(systems_[sys_type], [](auto &&ptr) {
            return ptr->get_name() == TSystem::class_name();
        });
    }

    template <typename... TSystems>
    bool system_manager::has_systems() const noexcept
    {
        return (has_system<TSystems>() && ...);
    }

    template <typename TSystem>
    bool system_manager::mark_system() noexcept
    {
        static_assert(details::is_system_v<TSystem>,
                      "The system type given as template parameter doesn't seems to be valid");
        if (has_system<TSystem>()) {
            get_system<TSystem>().mark();
            need_to_sweep_systems_ = true;
            return true;
        }
        need_to_sweep_systems_ = false;
        return false;
    }

    template <typename... TSystems>
    bool system_manager::mark_systems() noexcept
    {
        return (mark_system<TSystems>() && ...);
    }

    template <typename TSystem>
    bool system_manager::enable_system() noexcept
    {
        static_assert(details::is_system_v<TSystem>,
                      "The system type given as template parameter doesn't seems to be valid");
        if (has_system<TSystem>()) {
            get_system<TSystem>().enable();
            return true;
        }
        return false;
    }

    template <typename... TSystems>
    bool system_manager::enable_systems() noexcept
    {
        return (enable_system<TSystems>() && ...);
    }

    template <typename TSystem>
    bool system_manager::disable_system() noexcept
    {
        static_assert(details::is_system_v<TSystem>,
                      "The system type given as template parameter doesn't seems to be valid");
        if (has_system<TSystem>()) {
            get_system<TSystem>().disable();
            return true;
        }
        return false;
    }

    template <typename... TSystems>
    bool system_manager::disable_systems() noexcept
    {
        return (disable_system<TSystems>() && ...);
    }

    template <typename TSystem, typename... TSystemArgs>
    TSystem &system_manager::create_system(TSystemArgs &&... args) noexcept
    {
        static_assert(details::is_system_v<TSystem>,
                      "The system type given as template parameter doesn't seems to be valid");
        auto creator = [this](auto &&... args_) {
            return std::make_unique<TSystem>(this->dispatcher_,
                                             this->ett_registry_,
                                             this->timestep_.get_fixed_delta_time(),
                                             std::forward<decltype(args_)>(args_)...);
        };
        system_ptr sys = creator(std::forward<TSystemArgs>(args)...);
        return static_cast<TSystem &>(add_system_(std::move(sys), TSystem::get_system_type()));
    }

    template <typename... TSystems, typename... TArgs>
    auto system_manager::load_systems(TArgs &&...args) noexcept
    {
        (create_system<TSystems>(std::forward<TArgs>(args)...), ...);
        return get_systems<TSystems ...>();
    }

    size_t system_manager::nb_systems() const noexcept
    {
        return std::accumulate(std::begin(systems_), std::end(systems_), static_cast<size_t>(0u),
                               [](size_t accumulator, auto &&vec) {
                                   return accumulator + vec.size();
                               });
    }

    size_t system_manager::nb_systems(system_type sys_type) const noexcept
    {
        return systems_[sys_type].size();
    }

    bool system_manager::load_plugins() noexcept
    {
        auto res = plugins_registry_.load_all_symbols();
        auto functor = [this](auto &&dlls) {
            system_ptr ptr = dlls.second.creator_function(this->dispatcher_, this->ett_registry_,
                                                          this->timestep_.get_fixed_delta_time());
            dlls.second.class_name = ptr->get_name();
            dlls.second.type = static_cast<unsigned int>(ptr->get_system_type_RTTI());
            add_system_(std::move(ptr), ptr->get_system_type_RTTI()).im_a_plugin();
        };

        plugins_registry_.apply_on_each_symbols(functor);
        dispatcher_.trigger<shiva::event::after_load_systems_plugins>();
        return res;
    }

    bool system_manager::hot_reload_plugins() noexcept
    {
        plugins_registry_.apply_on_each_symbols([this](auto &&dlls) {
            if (shiva::fs::last_write_time(dlls.first) != dlls.second.last_write_time) {
                this->log_->info("{} -> need hot reload", dlls.first);
                auto &&system_collection = systems_[static_cast<system_type>(dlls.second.type)];
                auto it = shiva::ranges::find_if(system_collection, [&dlls](auto &&sys) {
                    return sys->get_name() == dlls.second.class_name;
                });
                if (it != system_collection.end()) {
                    it->reset(nullptr);
                    *it = std::move(dlls.second.creator_function(this->dispatcher_, this->ett_registry_,
                                                                 this->timestep_.get_fixed_delta_time()));
                    this->dispatcher_.trigger<shiva::event::after_system_reload_plugins>((*it).get());
                }
                dlls.second.last_write_time = shiva::fs::last_write_time(dlls.first);
            }
        });
        return true;
    }

    const base_system *
    system_manager::get_system_by_name(std::string system_name, shiva::ecs::system_type type) const noexcept
    {
        auto &&system_collection = systems_[type];
        auto it = shiva::ranges::find_if(system_collection, [name = std::move(system_name)](auto &&sys) {
            return sys->get_name() == name;
        });
        return (it != system_collection.end()) ? (*it).get() : nullptr;
    }

    base_system *system_manager::get_system_by_name(std::string system_name, shiva::ecs::system_type type) noexcept
    {
        auto &&system_collection = systems_[type];
        auto it = shiva::ranges::find_if(system_collection, [name = std::move(system_name)](auto &&sys) {

            return sys->get_name() == name;
        });
        return (it != system_collection.end()) ? (*it).get() : nullptr;
    }

    //! Private member functions

    base_system &system_manager::add_system_(system_manager::system_ptr &&system, system_type sys_type) noexcept
    {
        log_->info("successfully added system: {}", system->get_name());
        return *systems_[sys_type].emplace_back(std::move(system));
    }

    template <typename TSystem>
    tl::expected<std::reference_wrapper<TSystem>, std::error_code> system_manager::get_system_() noexcept
    {
        static_assert(details::is_system_v<TSystem>,
                      "The system type given as template parameter doesn't seems to be valid");


        if (!nb_systems(TSystem::get_system_type())) {
            return tl::make_unexpected(std::make_error_code(std::errc::result_out_of_range));
        }

        constexpr const auto sys_type = TSystem::get_system_type();
        auto it = shiva::ranges::find_if(systems_[sys_type], [](auto &&ptr) {
            return ptr->get_name() == TSystem::class_name();
        });

        if (it != systems_[sys_type].end()) {
            auto &system = static_cast<TSystem &>(*(*it));
            return std::reference_wrapper<TSystem>(system);
        }
        return tl::make_unexpected(std::make_error_code(std::errc::result_out_of_range));
    }

    template <typename TSystem>
    tl::expected<std::reference_wrapper<const TSystem>, std::error_code> system_manager::get_system_() const noexcept
    {
        static_assert(details::is_system_v<TSystem>,
                      "The system type given as template parameter doesn't seems to be valid");

        if (!nb_systems(TSystem::get_system_type())) {
            return tl::make_unexpected(std::make_error_code(std::errc::result_out_of_range));
        }

        constexpr const auto sys_type = TSystem::get_system_type();
        auto it = shiva::ranges::find_if(systems_[sys_type], [](auto &&ptr) {
            return ptr->get_name() == TSystem::class_name();
        });
        if (it != systems_[sys_type].end()) {
            const auto &system = static_cast<const TSystem &>(*(*it));
            return std::reference_wrapper<const TSystem>(system);
        }
        return tl::make_unexpected(std::make_error_code(std::errc::result_out_of_range));
    }

    void system_manager::sweep_systems_() noexcept
    {
        shiva::ranges::for_each(systems_, [](auto &&vec_system) -> void {
            vec_system.erase(std::remove_if(std::begin(vec_system), std::end(vec_system), [](auto &&sys) {
                return sys->is_marked();
            }), std::end(vec_system));
        });
        this->need_to_sweep_systems_ = false;
    }

    bool system_manager::prioritize_system(const std::string &system_to_swap, const std::string &system_b,
                                           shiva::ecs::system_type sys_type) noexcept
    {
        auto &&system_collection = systems_[sys_type];
        auto it_system_to_swap = shiva::ranges::find_if(system_collection, [name = system_to_swap](auto &&sys) {
            return sys->get_name() == name;
        });
        auto it_system_b = shiva::ranges::find_if(system_collection, [name = system_b](auto &&sys) {
            return sys->get_name() == name;
        });
        if (it_system_to_swap != systems_[sys_type].end() && it_system_b != systems_[sys_type].end()) {
            if (it_system_to_swap > it_system_b) {
                this->log_->info("{} > {}: swapp position", system_to_swap, system_b);
                std::iter_swap(it_system_to_swap, it_system_b);
            }
            return true;
        }
        return false;
    }

    size_t system_manager::update_systems(shiva::ecs::system_type system_type_to_update) noexcept
    {
        size_t nb_systems_updated = 0u;
        auto &&systems_collection_to_update = systems_[system_type_to_update];
        for (auto &&sys : systems_collection_to_update) {
            if (sys->is_enabled()) {
                sys->update();
                nb_systems_updated++;
            }
        }
        return nb_systems_updated;
    }
}
