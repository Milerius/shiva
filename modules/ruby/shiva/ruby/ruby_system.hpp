//
// Created by syl on 21/09/2018.
//

#pragma once

#include <shiva/ecs/system.hpp>

namespace shiva::ruby
{
    class ruby_system : public ecs::logic_update_system<ruby_system>
    {
        private:
            template <typename Component>
            void register_component_() noexcept:
    };
}