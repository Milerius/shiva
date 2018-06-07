//
// Created by roman Sztergbaum on 06/06/2018.
//

#pragma once

#include <utility>
#include <shiva/ecs/base_system.hpp>
#include <shiva/ecs/details/system_type_traits.hpp>

namespace shiva::ecs
{
    template <typename system_derived, typename t_system_type>
    class system : public base_system
    {
    private:
        template <typename T>
        using is_kind_system = std::is_same<t_system_type, T>;

    public:
        template <typename ...Args>
        explicit system(Args &&...args) noexcept : base_system(std::forward<Args>(args)...)
        {
        }

        ~system() noexcept override = default;

        static constexpr system_type get_system_type() noexcept
        {
            using is_same_list = meta::list::Transform<details::valid_systems_list, is_kind_system>;
            static_assert(details::is_valid_system_v(is_same_list{}), "valid_system_list is an invalid template parameter");
            if constexpr (std::is_same_v<t_system_type, system_logic_update>)
                return system_type::logic_update;
            else if constexpr (std::is_same_v<t_system_type, system_pre_update>)
                return system_type::pre_update;
            else if constexpr (std::is_same_v<t_system_type, system_post_update>)
                return system_type::post_update;
        }

        //! Override functions
        void update() noexcept override = 0;

        const std::string &getName() const noexcept final
        {
            return system_derived::class_name();
        }

    private:
    };
}
