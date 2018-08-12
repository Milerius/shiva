//
// Created by roman Sztergbaum on 15/06/2018.
//

#include <boost/dll.hpp>
#include <shiva/sfml/graphics/system-sfml-graphics.hpp>

namespace shiva::plugins
{
    //! Constructor
    render_system::render_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                                 const float &fixed_delta_time) noexcept :
        system(dispatcher, registry, fixed_delta_time, true)
    {
        user_data_ = &win_;
    }

    //! Public static functions
    std::unique_ptr<shiva::ecs::base_system> render_system::system_creator(shiva::entt::dispatcher &dispatcher,
                                                                           shiva::entt::entity_registry &registry,
                                                                           const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::render_system>(dispatcher, registry, fixed_delta_time);
    }

    //! Public member functions overriden
    void render_system::update() noexcept
    {
        auto draw = [this]([[maybe_unused]] auto entity, [[maybe_unused]] auto &&layer, auto &&drawable) {
            this->win_.draw(*std::static_pointer_cast<sf::Drawable>(drawable.drawable_));
        };

        win_.clear();
        entity_registry_.view<shiva::ecs::layer_1, shiva::ecs::drawable>().each(draw);
        entity_registry_.view<shiva::ecs::layer_2, shiva::ecs::drawable>().each(draw);
        entity_registry_.view<shiva::ecs::layer_3, shiva::ecs::drawable>().each(draw);
        entity_registry_.view<shiva::ecs::layer_4, shiva::ecs::drawable>().each(draw);
        entity_registry_.view<shiva::ecs::layer_5, shiva::ecs::drawable>().each(draw);
        entity_registry_.view<shiva::ecs::layer_6, shiva::ecs::drawable>().each(draw);
        entity_registry_.view<shiva::ecs::layer_7, shiva::ecs::drawable>().each(draw);
        entity_registry_.view<shiva::ecs::layer_8, shiva::ecs::drawable>().each(draw);
        win_.display();
    }

    //! Reflection
    constexpr auto render_system::reflected_functions() noexcept
    {
        return meta::makeMap(reflect_function(&render_system::update));
    }

    constexpr auto render_system::reflected_members() noexcept
    {
        return meta::makeMap();
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::render_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
