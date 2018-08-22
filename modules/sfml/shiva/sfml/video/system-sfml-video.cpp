//
// Created by roman Sztergbaum on 19/08/2018.
//

#include <boost/dll.hpp>
#include <shiva/ecs/opaque_data.hpp>
#include <shiva/sfml/common/drawable_component_impl.hpp>
#include "system-sfml-video.hpp"

namespace shiva::plugins
{
    //! Constructor
    video_system::video_system(shiva::entt::dispatcher &dispatcher,
                               shiva::entt::entity_registry &registry,
                               const float &fixed_delta_time) noexcept :
        system(dispatcher, registry, fixed_delta_time, true)
    {
    }

    //! Public static functions
    std::unique_ptr<shiva::ecs::base_system>
    video_system::system_creator(entt::dispatcher &dispatcher, entt::entity_registry &registry,
                                 const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::video_system>(dispatcher, registry, fixed_delta_time);
    }

    void video_system::update() noexcept
    {
        entity_registry_.view<shiva::ecs::video, shiva::ecs::drawable>().each([this]([[maybe_unused]] auto entity,
                                                                                     auto &&video,
                                                                                     auto &&drawable) {

            auto video_ptr = std::static_pointer_cast<sfe::Movie>(
                std::static_pointer_cast<shiva::sfml::drawable_component_impl>(drawable.drawable_)->concrete);
            auto video_info_ptr = std::static_pointer_cast<shiva::sfml::video_component_impl>(video.video_);

            //! I'm playing the video
            if (video_info_ptr->current_status == status_t::playing)
                video_ptr->update();

            //! Video is end
            if (video_ptr->getStatus() == sfe::Status::End || video_ptr->getStatus() == sfe::Status::Stopped) {
                video_info_ptr->current_status = status_t::stopped;
                if (video_info_ptr->functor != sol::lua_nil) {
                    video_info_ptr->functor();
                }
                this->disable();
            }
        });
    }

    entt::entity_registry::entity_type
    video_system::create_game_object_with_video(video_system::status_t::EnumType status, const char *video_id,
                                                sol::function func) noexcept
    {
        auto entity_id = this->entity_registry_.create();
        add_video_(entity_id, status, video_id, func);
        return entity_id;
    }

    constexpr auto video_system::reflected_functions() noexcept
    {
        return meta::makeMap(reflect_function(&video_system::create_game_object_with_video));
    }

    constexpr auto video_system::reflected_members() noexcept
    {
        return meta::makeMap();
    }

    void video_system::on_set_user_data_() noexcept
    {
        auto opaque_data = static_cast<shiva::ecs::opaque_data *>(user_data_);
        state_ = static_cast<sol::state *>(opaque_data->data_1);
        win_ = static_cast<sf::RenderWindow *>(opaque_data->data_2);

        shiva::lua::register_type<video_system>(*state_, log_);
        state_->new_enum<status_t::EnumType>("video_status",
                                             {
                                                 {"playing", static_cast<status_t::EnumType>(status_t::playing)},
                                                 {"paused",  static_cast<status_t::EnumType>(status_t::paused)},
                                                 {"stopped", static_cast<status_t::EnumType>(status_t::stopped)}
                                             });

        (*state_)["shiva"]["video"] = std::ref(*this);
    }

    void video_system::add_video_(entt::entity_registry::entity_type entity,
                                  video_system::status_t status,
                                  const char *video_id,
                                  sol::function func) noexcept
    {
        sol::table
            self = (*state_)["shiva"]["resource_registry"];
        const sfe::Movie &movie = self["get_video_c"](self, video_id);
        //! Drawable
        auto movie_ptr = std::make_shared<sfe::Movie>(movie);
        entity_registry_.assign<shiva::ecs::drawable>(entity,
                                                      std::make_shared<shiva::sfml::drawable_component_impl>(
                                                          movie_ptr,
                                                          std::static_pointer_cast<sf::Drawable>(movie_ptr),
                                                          std::static_pointer_cast<sf::Transformable>(movie_ptr)));

        auto &video_component = entity_registry_.assign<shiva::ecs::video>(entity,
                                                                           std::make_shared<shiva::sfml::video_component_impl>());

        auto video_component_impl = std::static_pointer_cast<shiva::sfml::video_component_impl>(video_component.video_);
        video_component_impl->current_status = status;
        video_component_impl->title = video_id;
        if (func != sol::lua_nil) {
            video_component_impl->functor = std::move(func);
            assert(video_component_impl->functor != sol::lua_nil);
        }
        this->log_->info("movie duration {}\n movie status {}\n movie title {}",
                         movie_ptr->getDuration().asSeconds(),
                         status.toString(),
                         video_id);
        movie_ptr->fit(0.f, 0.f, static_cast<float>(win_->getSize().x), static_cast<float>(win_->getSize().y));
        sf::Time time;
        movie_ptr->setPlayingOffset(time);
        switch (video_component_impl->current_status) {
            case video_system::status_t::playing:
                movie_ptr->play();
                break;
            case video_system::status_t::paused:
                movie_ptr->pause();
                break;
            case video_system::status_t::stopped:
                movie_ptr->stop();
                break;
        }
        this->enable();
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::video_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
