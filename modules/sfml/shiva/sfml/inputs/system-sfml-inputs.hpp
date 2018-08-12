//
// Created by roman Sztergbaum on 18/06/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <shiva/entt/entt.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/entt/entt_config.hpp>

namespace shiva::plugins
{
    class input_system final : public shiva::ecs::pre_update_system<input_system>
    {
    public:
        //! Destructor
        ~input_system() noexcept final = default;

        //! Constructor
        input_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                     const float &fixed_delta_time) noexcept;

        //! Public static functions
        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;

        //! Public member functions overriden
        void update() noexcept final;

        //! Reflection
        reflect_class(input_system)

        static constexpr auto reflected_functions() noexcept;

        static constexpr auto reflected_members() noexcept;

    private:
        //! Private member functions overriden
        void on_set_user_data_() noexcept final;

        //! Private data members
        sf::RenderWindow *win_{nullptr};
    };
}