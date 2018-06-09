//
// Created by roman Sztergbaum on 31/05/2018.
//

#pragma once

#include <EASTL/algorithm.h>
#include <EASTL/utility.h>
#include <EASTL/allocator_malloc.h>
#include <EASTL/vector.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/array.h>
#include <shiva/range/range.hpp>
#include <shiva/stacktrace/stacktrace.hpp>
#include <shiva/error/expected.hpp>
#include <shiva/ecs/using_alias_library.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/ecs/system_type.hpp>
#include <shiva/event/fatal_error_occured.hpp>
#include <shiva/event/quit_game.hpp>

namespace shiva::ecs
{
    class system_manager
    {
    public:
        using system_ptr = eastl::unique_ptr<base_system>;
        using system_array = eastl::vector<system_ptr, eastl::allocator_malloc>;
        using system_registry = eastl::array<system_array, size>;

        //! Callbacks
        void receive([[maybe_unused]] const shiva::event::quit_game &evt)
        {
        }

        explicit system_manager(entt::dispatcher &dispatcher, entt::entity_registry &registry) noexcept :
            dispatcher_(dispatcher),
            ett_registry_(registry)
        {
            dispatcher_.sink<shiva::event::quit_game>().connect(this);
        }

        size_t update() noexcept
        {
            return 0;
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

        template <typename TSystem, typename ... SystemArgs>
        TSystem &create_system(SystemArgs &&...args)
        {
            static_assert(details::is_system_v<TSystem>,
                          "The system type given as template parameter doesn't seems to be valid");
            auto creator = [this](auto &&... args) {
                return eastl::make_unique<TSystem>(this->dispatcher_, this->ett_registry_,
                                                   eastl::forward<decltype(args)>(args)...);
            };
            system_ptr sys = creator(eastl::forward<SystemArgs>(args)...);
            return static_cast<TSystem &>(add_system_<TSystem>(eastl::move(sys)));
        }

        template <typename ...TSystems>
        decltype(auto) load_systems()
        {
            (create_system<TSystems>(), ...);
            return get_systems<TSystems ...>();
        }

        size_t nb_systems() const noexcept
        {
            return std::accumulate(eastl::begin(systems_), eastl::end(systems_), static_cast<size_t>(0u),
                                   [](size_t accumulator, auto &&vec) {
                                       return accumulator + vec.size();
                                   });
        }

        size_t nb_systems(system_type sys_type) const noexcept
        {
            return systems_[sys_type].size();
        }

    private:
        template <typename TSystem>
        base_system &add_system_(system_ptr &&system) noexcept
        {
            return *systems_[TSystem::get_system_type()].emplace_back(eastl::move(system));
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

        system_registry systems_{{}};
        entt::dispatcher &dispatcher_;
        entt::entity_registry &ett_registry_;
    };
}
