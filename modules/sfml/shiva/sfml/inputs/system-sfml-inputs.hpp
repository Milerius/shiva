//
// Created by roman Sztergbaum on 18/06/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <shiva/entt_shared/entt_shared.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/sfml/event/set_render_window.hpp>

namespace shiva::plugins
{
    class input_system : public shiva::ecs::pre_update_system<input_system>
    {
    public:
        virtual void on_set_user_data() noexcept final
        {
            log_->info("SALUT SALUT");
            win_ = reinterpret_cast<sf::RenderWindow *>(user_data_);
        }

        ~input_system() noexcept override = default;

        input_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                     const float &fixed_delta_time) noexcept :
            system(dispatcher, registry, fixed_delta_time)
        {
            shiva::entt_shared::init_library(entity_registry_, dispatcher_);
        }

        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;
        void update() noexcept final;

    public:
        reflect_class(input_system)

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap(reflect_function(&input_system::update));
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

    private:
        sf::RenderWindow *win_{nullptr};
    };
}