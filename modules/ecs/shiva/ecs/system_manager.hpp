//
// Created by roman Sztergbaum on 31/05/2018.
//

#pragma once

#include <memory>
#include <shiva/range/range.hpp>
#include <shiva/error/expected.hpp>
#include <shiva/ecs/using_alias_library.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/ecs/system_type.hpp>
#include <shiva/event/fatal_error_occured.hpp>
#include <shiva/event/quit_game.hpp>
#include <shiva/event/start_game.hpp>
#include <shiva/event/after_load_systems_plugins.hpp>
#include <shiva/event/add_base_system.hpp>
#include <shiva/dll/plugins_registry.hpp>
#include <shiva/timer/timestep.hpp>
#include <shiva/spdlog/spdlog.hpp>

namespace shiva::ecs
{
    class system_manager
    {
    public:
        using system_ptr = std::unique_ptr<base_system>;
        using system_array = std::vector<system_ptr>;
        using system_registry = std::array<system_array, size>;
        typedef system_ptr (pluginapi_create_t)(shiva::entt::dispatcher &, shiva::entt::entity_registry &,
                                                const float &fixed_delta_time);
        using plugins_registry_t = shiva::helpers::plugins_registry<pluginapi_create_t>;

        //! Callbacks
        void receive([[maybe_unused]] const shiva::event::quit_game &evt)
        {
            log_->info("quit_game event received");
            shiva::ranges::for_each(systems_, [](auto &&vec) {
                shiva::ranges::for_each(vec, [](auto &&sys) {
                    sys->disable();
                });
            });
        }

        void receive([[maybe_unused]] const shiva::event::start_game &evt)
        {
            timestep_.start();
        }

        void receive(const shiva::event::add_base_system &evt)
        {
            add_system_(std::move(const_cast<shiva::event::add_base_system &>(evt).system_ptr),
                        evt.system_ptr->get_system_type_RTTI());
        }

        explicit system_manager(entt::dispatcher &dispatcher,
                                entt::entity_registry &registry,
                                plugins_registry_t &plugins_registry) noexcept :
            dispatcher_(dispatcher),
            ett_registry_(registry),
            plugins_registry_(plugins_registry)
        {
            dispatcher_.sink<shiva::event::start_game>().connect(this);
            dispatcher_.sink<shiva::event::quit_game>().connect(this);
            dispatcher_.sink<shiva::event::add_base_system>().connect(this);
            log_->info("system_manager successfully created");
        }

        size_t update() noexcept
        {
            if (!nb_systems())
                return 0u;
            size_t nb_systems_updated = 0u;

            auto update_system_functor = [&nb_systems_updated](auto &&sys) {
                if (sys->is_enabled()) {
                    sys->update();
                    nb_systems_updated++;
                }
            };

            shiva::ranges::for_each(systems_, [this, update_system_functor](auto &&vec) {
                if (!vec.empty()) {
                    system_type current_system_type = vec.front()->get_system_type_RTTI();
                    auto update_functor = [this, update_system_functor, current_system_type]() {
                        shiva::ranges::for_each(this->systems_[current_system_type],
                                                [update_system_functor](auto &&sys) {
                                                    update_system_functor(std::forward<decltype(sys)>(sys));
                                                });
                    };

                    if (current_system_type != system_type::logic_update) {
                        update_functor();
                    } else {
                        timestep_.start_frame();
                        while (timestep_.is_update_required()) {
                            update_functor();
                            timestep_.perform_update();
                        }
                    }
                };
            });

            if (need_to_sweep_systems_) {
                sweep_systems_();
            }

            return nb_systems_updated;
        }

        template <typename TSystem>
        const TSystem &get_system() const
        {
            const auto ret = get_system_<TSystem>().or_else([this](const std::error_code &ec) {
                this->dispatcher_.trigger<shiva::event::fatal_error_occured>(ec);
            });
            return (*ret).get();
        }

        template <typename TSystem>
        TSystem &get_system()
        {
            auto ret = get_system_<TSystem>().or_else([this](const std::error_code &ec) {
                this->dispatcher_.trigger<shiva::event::fatal_error_occured>(ec);
            });
            return (*ret).get();
        }

        template <typename ...Systems>
        std::tuple<std::add_lvalue_reference_t<Systems>...> get_systems()
        {
            return {get_system<Systems>()...};
        }

        template <typename ...Systems>
        std::tuple<std::add_lvalue_reference_t<std::add_const_t<Systems>>...> get_systems() const
        {
            return {get_system<Systems>()...};
        }

        template <typename TSystem>
        bool has_system() const noexcept
        {
            static_assert(details::is_system_v<TSystem>,
                          "The system type given as template parameter doesn't seems to be valid");
            constexpr const auto sys_type = TSystem::get_system_type();
            return shiva::ranges::any_of(systems_[sys_type], [](auto &&ptr) {
                return ptr->get_name() == TSystem::class_name();
            });
        }

        template <typename ... Systems>
        bool has_systems() const noexcept
        {
            return (has_system<Systems>() && ...);
        }

        template <typename TSystem>
        bool mark_system() noexcept
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

        template <typename ... Systems>
        bool mark_systems() noexcept
        {
            return (mark_system<Systems>() && ...);
        }

        template <typename TSystem>
        bool enable_system() noexcept
        {
            static_assert(details::is_system_v<TSystem>,
                          "The system type given as template parameter doesn't seems to be valid");
            if (has_system<TSystem>()) {
                get_system<TSystem>().enable();
                return true;
            }
            return false;
        }

        template <typename ... Systems>
        bool enable_systems() noexcept
        {
            return (enable_system<Systems>() && ...);
        }

        template <typename TSystem>
        bool disable_system() noexcept
        {
            static_assert(details::is_system_v<TSystem>,
                          "The system type given as template parameter doesn't seems to be valid");
            if (has_system<TSystem>()) {
                get_system<TSystem>().disable();
                return true;
            }
            return false;
        }

        template <typename ... Systems>
        bool disable_systems() noexcept
        {
            return (disable_system<Systems>() && ...);
        }

        template <typename TSystem, typename ... SystemArgs>
        TSystem &create_system(SystemArgs &&...args)
        {
            static_assert(details::is_system_v<TSystem>,
                          "The system type given as template parameter doesn't seems to be valid");
            auto creator = [this](auto &&... args) {
                return std::make_unique<TSystem>(this->dispatcher_,
                                                 this->ett_registry_,
                                                 this->timestep_.get_fixed_delta_time(),
                                                 std::forward<decltype(args)>(args)...);
            };
            system_ptr sys = creator(std::forward<SystemArgs>(args)...);
            return static_cast<TSystem &>(add_system_(std::move(sys), TSystem::get_system_type()));
        }

        template <typename ...TSystems>
        decltype(auto) load_systems()
        {
            (create_system<TSystems>(), ...);
            return get_systems<TSystems ...>();
        }

        size_t nb_systems() const noexcept
        {
            return std::accumulate(std::begin(systems_), std::end(systems_), static_cast<size_t>(0u),
                                   [](size_t accumulator, auto &&vec) {
                                       return accumulator + vec.size();
                                   });
        }

        size_t nb_systems(system_type sys_type) const noexcept
        {
            return systems_[sys_type].size();
        }

        bool load_plugins() noexcept
        {
            auto res = plugins_registry_.load_all_symbols();
            auto functor = [this](auto &&dlls) {
                system_ptr ptr = dlls(this->dispatcher_, this->ett_registry_, this->timestep_.get_fixed_delta_time());
                add_system_(std::move(ptr), ptr->get_system_type_RTTI()).im_a_plugin();
            };

            plugins_registry_.apply_on_each_symbols(functor);
            dispatcher_.trigger<shiva::event::after_load_systems_plugins>();
            return res;
        }

        const base_system *get_system_by_name(std::string system_name, shiva::ecs::system_type type) const noexcept
        {
            auto &&system_collection = systems_[type];
            auto it = shiva::ranges::find_if(system_collection, [name = std::move(system_name)](auto &&sys) {
                return sys->get_name() == name;
            });
            return (it != system_collection.end()) ? (*it).get() : nullptr;
        }

        base_system *get_system_by_name(std::string system_name, shiva::ecs::system_type type) noexcept
        {
            auto &&system_collection = systems_[type];
            auto it = shiva::ranges::find_if(system_collection, [name = std::move(system_name)](auto &&sys) {
                return sys->get_name() == name;
            });
            return (it != system_collection.end()) ? (*it).get() : nullptr;
        }

    private:
        base_system &add_system_(system_ptr &&system, system_type sys_type) noexcept
        {
            log_->info("successfully added system: {}", system->get_name());
            return *systems_[sys_type].emplace_back(std::move(system));
        }

        template <typename TSystem>
        tl::expected<std::reference_wrapper<TSystem>, std::error_code> get_system_() noexcept
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
        };

        template <typename TSystem>
        tl::expected<std::reference_wrapper<const TSystem>, std::error_code> get_system_() const noexcept
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
        };

        void sweep_systems_() noexcept
        {
            shiva::ranges::for_each(systems_, [](auto &&vec_system) -> void {
                vec_system.erase(std::remove_if(std::begin(vec_system), std::end(vec_system), [](auto &&sys) {
                    return sys->is_marked();
                }), std::end(vec_system));
            });
        }

        shiva::timer::time_step timestep_;
        entt::dispatcher &dispatcher_;
        entt::entity_registry &ett_registry_;
        plugins_registry_t &plugins_registry_;
        system_registry systems_{{}};
        bool need_to_sweep_systems_{false};
        std::shared_ptr<spdlog::logger> log_{shiva::log::stdout_color_mt("system_manager")};
    };
}
