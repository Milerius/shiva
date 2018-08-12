//
// Created by roman Sztergbaum on 05/08/2018.
//

#include <boost/dll.hpp>
#include <shiva/sfml/animation/system-sfml-animation.hpp>

namespace shiva::plugins
{
    //! Constructor
    animation_system::animation_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                                       const float &fixed_delta_time) noexcept :
        system(dispatcher, registry, fixed_delta_time, true)
    {
    }

    //! Private member functions overriden
    void animation_system::on_set_user_data_() noexcept
    {
        state_ = static_cast<sol::state *>(user_data_);
        shiva::lua::register_type<animation_system>(*state_, log_);
        state_->new_enum<status_t>("anim_status",
                                   {
                                       {"playing", status_t::playing},
                                       {"paused",  status_t::paused},
                                       {"stopped", status_t::stopped}
                                   });
        (*state_)["shiva"]["anim"] = std::ref(*this);
    }

    //! Public member functions overriden
    void animation_system::update() noexcept
    {
        sf::Time delta_time = sf::seconds(static_cast<float>(fixed_delta_time_));
        auto animation_update_functor = [this, &delta_time](auto entity, [[maybe_unused]] auto &&animation_component) {
            auto animation_ptr = this->get_animation_ptr_(entity);
            if (animation_ptr->current_status == status_t::playing) {
                animation_ptr->elapsed += delta_time;
                if (animation_ptr->elapsed > animation_ptr->delta) {
                    animation_ptr->elapsed -= animation_ptr->delta;
                    if (animation_ptr->current_frame + 1 < size(entity)) {
                        ++animation_ptr->current_frame;
                    } else {
                        if (animation_ptr->loop)
                            animation_ptr->current_frame = 0;
                        if (!animation_ptr->loop) {
                            --animation_ptr->repeat;
                            if (animation_ptr->repeat <= 0) {
                                animation_ptr->current_status = status_t::stopped;
                            }
                        }
                    }
                }
                set_frame_(entity, false);
            }
        };
        entity_registry_.view<shiva::ecs::animation>().each(animation_update_functor);
    }

    //! Public static functions
    std::unique_ptr<shiva::ecs::base_system>
    animation_system::system_creator(entt::dispatcher &dispatcher,
                                     entt::entity_registry &registry,
                                     const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::animation_system>(dispatcher, registry, fixed_delta_time);
    }

    //! Public member functions
    animation_system::status_t animation_system::get_status(entt::entity_registry::entity_type entity) const noexcept
    {
        const auto animation_ptr = get_animation_ptr_(entity);
        return animation_ptr->current_status;
    }

    void animation_system::set_status(entt::entity_registry::entity_type entity,
                                      status_t status) noexcept
    {
        auto animation_ptr = get_animation_ptr_(entity);
        animation_ptr->current_status = status;
    }

    entt::entity_registry::entity_type animation_system::create_game_object_with_animated_sprite(status_t status,
                                                                                                 double delta_time,
                                                                                                 bool loop,
                                                                                                 int repeat,
                                                                                                 unsigned int nb_columns,
                                                                                                 unsigned int nb_lines,
                                                                                                 unsigned int nb_anims,
                                                                                                 const char *texture_name) noexcept
    {
        auto entity_id = this->entity_registry_.create();

        //! Drawable
        auto &drawable_component = entity_registry_.assign<shiva::ecs::drawable>(entity_id,
                                                                                 std::make_shared<sf::Sprite>());

        sol::table
        self = (*state_)["shiva"]["resource_registry"];
        const sf::Texture &texture = self["get_texture_c"](self, texture_name);

        std::static_pointer_cast<sf::Sprite>(drawable_component.drawable_)->setTexture(texture);

        //! Animation
        entity_registry_.assign<shiva::ecs::animation>(entity_id,
                                                       std::make_shared<shiva::sfml::animation_component_impl>());
        auto animation_ptr = get_animation_ptr_(entity_id);
        sf::Time delta_time_sfml = sf::seconds(static_cast<float>(delta_time));
        animation_ptr->current_status = status;
        animation_ptr->delta = delta_time_sfml;
        animation_ptr->loop = loop;
        animation_ptr->repeat = repeat;
        animation_ptr->elapsed = sf::Time::Zero;
        animation_ptr->current_frame = 0;
        add_one_shot_animation(entity_id, nb_columns, nb_lines, nb_anims);
        set_frame(entity_id, 0);
        return entity_id;
    }

    const sf::IntRect &
    animation_system::get_rect(entt::entity_registry::entity_type entity, size_t index) const noexcept
    {
        return get_animation_ptr_(entity)->frames[index];
    }

    //anim_last_line, nb_lines, nb_lines - 1, nb_columns
    void animation_system::add_frames_line(entt::entity_registry::entity_type entity, unsigned int numberX,
                                           unsigned int numberY, unsigned int line, unsigned int columns) noexcept
    {

        const sf::Vector2u size = std::static_pointer_cast<sf::Sprite>(
            entity_registry_.get<shiva::ecs::drawable>(entity).drawable_)->getTexture()->getSize();
        const float delta_x = (numberY == 1) ? (size.x / float(columns * numberX)) : (size.x / float(columns));
        const float delta_y = size.y / float(numberY);

        for (unsigned int i = 0; i < numberX; ++i)
            add_frame(entity, sf::IntRect(static_cast<int>(i * delta_x),
                                          static_cast<int>(line * delta_y),
                                          static_cast<int>(delta_x),
                                          static_cast<int>(delta_y)));
    }

    void animation_system::add_frames_column(entt::entity_registry::entity_type entity, int numberX, int numberY,
                                             int column) noexcept
    {
        const sf::Vector2u size = std::static_pointer_cast<sf::Sprite>(
            entity_registry_.get<shiva::ecs::drawable>(entity).drawable_)->getTexture()->getSize();
        const float delta_x = size.x / float(numberX);
        const float delta_y = size.y / float(numberY);

        for (int i = 0; i < numberY; ++i)
            add_frame(entity, sf::IntRect(static_cast<int>(column * delta_x),
                                          static_cast<int>(i * delta_y),
                                          static_cast<int>(delta_x),
                                          static_cast<int>(delta_y)));
    }

    size_t animation_system::size(entt::entity_registry::entity_type entity) const noexcept
    {
        return get_animation_ptr_(entity)->frames.size();
    }

    void animation_system::add_frame(entt::entity_registry::entity_type entity, const sf::IntRect &rect) noexcept
    {
        get_animation_ptr_(entity)->frames.emplace_back(rect);
    }

    void animation_system::set_frame(entt::entity_registry::entity_type entity, size_t index) noexcept
    {
        auto animation_ptr = get_animation_ptr_(entity);
        animation_ptr->current_frame = index % size(entity);
        set_frame_(entity, true);
    }

    void animation_system::add_one_shot_animation(entt::entity_registry::entity_type entity,
                                                  unsigned int nb_columns,
                                                  unsigned int nb_lines,
                                                  unsigned int nb_anims) noexcept
    {
        auto end = nb_lines - 1;
        for (unsigned int i = 0; i < end; i++) {
            add_frames_line(entity, nb_columns, nb_lines, i, nb_columns);
        }
        auto anim_last_line = (nb_anims - ((nb_lines - 1) * nb_columns));

        add_frames_line(entity, anim_last_line, nb_lines, nb_lines - 1, nb_columns);
    }

    //! Private member functions
    std::shared_ptr<shiva::sfml::animation_component_impl>
    animation_system::get_animation_ptr_(entt::entity_registry::entity_type entity) noexcept
    {
        auto &animation_component = entity_registry_.get<shiva::ecs::animation>(entity);
        return std::static_pointer_cast<shiva::sfml::animation_component_impl>(
            animation_component.animation_);
    }

    const std::shared_ptr<shiva::sfml::animation_component_impl>
    animation_system::get_animation_ptr_(entt::entity_registry::entity_type entity) const noexcept
    {
        const auto &animation_component = entity_registry_.get<shiva::ecs::animation>(entity);
        return std::static_pointer_cast<shiva::sfml::animation_component_impl>(
            animation_component.animation_);
    }

    void animation_system::set_frame_(entt::entity_registry::entity_type entity, bool reset_time) noexcept
    {
        auto animation_ptr = get_animation_ptr_(entity);
        sf::IntRect rect = get_rect(entity, animation_ptr->current_frame);
        std::static_pointer_cast<sf::Sprite>(
            entity_registry_.get<shiva::ecs::drawable>(entity).drawable_)->setTextureRect(rect);
        if (reset_time)
            animation_ptr->elapsed = sf::Time::Zero;
    }

    //! Reflection
    constexpr auto animation_system::reflected_functions() noexcept
    {
        return meta::makeMap(reflect_function(&animation_system::update),
                             reflect_function(&animation_system::create_game_object_with_animated_sprite));
    }

    constexpr auto animation_system::reflected_members() noexcept
    {
        return meta::makeMap();
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::animation_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
