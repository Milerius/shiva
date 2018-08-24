//
// Created by roman Sztergbaum on 15/06/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <sfml-imgui/imgui-SFML.hpp>
#include <shiva/entt/entt.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/sfml/graphics/window_config.hpp>

namespace shiva::plugins
{
    class render_system final : public shiva::ecs::post_update_system<render_system>
    {
    public:
        //! Destructor
        ~render_system() noexcept final;

        //! Constructor
        render_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                      const float &fixed_delta_time) noexcept;

        //! Callbacks
        void receive(const shiva::event::key_pressed& evt);

        //! Public static functions
        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;

        //! Public member functions overriden
        void update() noexcept final;

        //! Reflection
        reflect_class(render_system)

        static constexpr auto reflected_functions() noexcept;

        static constexpr auto reflected_members() noexcept;

    private:
        //! Private member function
        void reload_json_configuration_() noexcept;

        //! Private data members
        shiva::sfml::window_config cfg_;
        sf::RenderWindow win_{sf::VideoMode(cfg_.size[0], cfg_.size[1]), cfg_.name};

        bool debug_draw_{false};
    };
}