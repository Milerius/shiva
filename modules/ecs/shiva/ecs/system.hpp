//
// Created by roman Sztergbaum on 06/06/2018.
//

#pragma once

#include <shiva/ecs/base_system.hpp>

namespace shiva::ecs
{
    template <typename system_derived>
    class system : public base_system
    {
    public:
        template <typename ...Args>
        explicit system(Args &&...args) noexcept : base_system(std::forward<Args>(args)...)
        {
        }

        ~system() noexcept override = default;

        void update() noexcept override = 0;

        const std::string &getName() const noexcept final
        {
            return system_derived::class_name();
        }

    private:
    };
}
