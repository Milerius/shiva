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
        using system_ptr = eastl::unique_ptr<shiva::ecs::base_system>;
        using system_array = eastl::vector<system_ptr, eastl::allocator_malloc>;
        using system_registry = eastl::array<system_array, system_type::size>;
    public:
        //! Callbacks
        void receive([[maybe_unused]] const shiva::event::quit_game &evt)
        {
        }
    public:
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

        template <typename t_system>
        const t_system &get_system() const
        {
            const auto ret = get_system_<t_system>().or_else([this](const std::error_code &ec) {
                this->dispatcher_.trigger<shiva::event::fatal_error_occured>(ec);
            });
            return (*ret).get();
        }

        template <typename t_system>
        t_system &get_system()
        {
            auto ret = get_system_<t_system>().or_else([this](const std::error_code &ec) {
                this->dispatcher_.trigger<shiva::event::fatal_error_occured>(ec);
            });
            return (*ret).get();
        }

        template <typename ...systems>
        std::tuple<std::add_lvalue_reference_t<systems>...> get_systems()
        {
            return {get_system<systems>()...};
        }

        template <typename ...systems>
        std::tuple<std::add_lvalue_reference_t<std::add_const_t<systems>>...> get_systems() const
        {
            return {get_system<systems>()...};
        }

        template <typename t_system>
        bool has_system() const noexcept
        {
            static_assert(details::is_system_v<t_system>,
                          "The system type given as template parameter doesn't seems to be valid");
            constexpr const auto sys_type = t_system::get_system_type();
            return eastl::any_of(eastl::begin(systems_[sys_type]), eastl::end(systems_[sys_type]), [](auto &&ptr) {
                return ptr->get_name() == t_system::class_name();
            });
        }

        template <typename ... systems>
        bool has_systems() const noexcept
        {
            return (has_system<systems>() && ...);
        }

        template <typename t_system, typename ... system_args>
        t_system &create_system(system_args &&...args)
        {
            static_assert(details::is_system_v<t_system>,
                          "The system type given as template parameter doesn't seems to be valid");
            auto creator = [this](auto &&... args) {
                return eastl::make_unique<t_system>(this->dispatcher_, this->ett_registry_,
                                                    eastl::forward<decltype(args)>(args)...);
            };
            system_ptr sys = creator(eastl::forward<system_args>(args)...);
            return static_cast<t_system &>(add_system_<t_system>(eastl::move(sys)));
        }

        size_t nb_systems() const noexcept
        {
            return std::accumulate(eastl::begin(systems_), eastl::end(systems_), 0u,
                                   [](size_t accumulator, auto &&vec) {
                                       return accumulator + vec.size();
                                   });
        }

        size_t nb_systems(system_type sys_type) const noexcept
        {
            return systems_[sys_type].size();
        }

    private:
        template <typename t_system>
        base_system &add_system_(system_ptr &&system) noexcept
        {
            return *systems_[t_system::get_system_type()].emplace_back(eastl::move(system));
        }

        template <typename t_system>
        tl::expected<std::reference_wrapper<t_system>, std::error_code> get_system_() noexcept
        {
            static_assert(details::is_system_v<t_system>,
                          "The system type given as template parameter doesn't seems to be valid");


            if (!nb_systems(t_system::get_system_type())) {
                return tl::make_unexpected(std::make_error_code(std::errc::result_out_of_range));
            }

            constexpr const auto sys_type = t_system::get_system_type();
            auto it = eastl::find_if(eastl::begin(systems_[sys_type]), eastl::end(systems_[sys_type]), [](auto &&ptr) {
                return ptr->get_name() == t_system::class_name();
            });
            if (it != systems_[sys_type].end()) {
                auto &system = static_cast<t_system &>(*(*it));
                return std::reference_wrapper<t_system>(system);
            }
            return tl::make_unexpected(std::make_error_code(std::errc::result_out_of_range));
        };

        template <typename t_system>
        const tl::expected<std::reference_wrapper<const t_system>, std::error_code> get_system_() const noexcept
        {
            static_assert(details::is_system_v<t_system>,
                          "The system type given as template parameter doesn't seems to be valid");

            if (!nb_systems(t_system::get_system_type())) {
                return tl::make_unexpected(std::make_error_code(std::errc::result_out_of_range));
            }

            constexpr const auto sys_type = t_system::get_system_type();
            auto it = eastl::find_if(eastl::cbegin(systems_[sys_type]), eastl::cend(systems_[sys_type]),
                                     [](auto &&ptr) {
                                         return ptr->get_name() == t_system::class_name();
                                     });
            if (it != systems_[sys_type].end()) {
                const auto &system = static_cast<const t_system &>(*(*it));
                return std::reference_wrapper<const t_system>(system);
            }
            return tl::make_unexpected(std::make_error_code(std::errc::result_out_of_range));
        };

    private:
        system_registry systems_{{}};
        entt::dispatcher &dispatcher_;
        entt::entity_registry &ett_registry_;
    };
}