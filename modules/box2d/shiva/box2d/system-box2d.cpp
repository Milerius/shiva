//
// Created by roman Sztergbaum on 16/08/2018.
//

#include <boost/dll.hpp>
#include <shiva/box2d/system-box2d.hpp>
#include <shiva/ecs/components/physics_2d.hpp>
#include "system-box2d.hpp"
#include "box2d_component.hpp"

namespace shiva::plugins
{
    //! Constructor
    box2d_system::box2d_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                               const float &fixed_delta_time) noexcept :
        system(dispatcher, registry, fixed_delta_time, true),
        listener_(dispatcher)
    {
        world_.SetContactListener(&listener_);
    }

    //! Public static functions
    std::unique_ptr<shiva::ecs::base_system>
    box2d_system::system_creator(entt::dispatcher &dispatcher, entt::entity_registry &registry,
                                 const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::box2d_system>(dispatcher, registry, fixed_delta_time);
    }

    //! Public member function overriden
    void box2d_system::update() noexcept
    {
        auto update_functor = []([[maybe_unused]] auto entity, auto &&transform, auto &&physics) {
            auto body = std::static_pointer_cast<shiva::box2d::box2d_component>(physics.physics_)->body;
            body->SetTransform(b2Vec2(transform.x, transform.y), body->GetAngle());
        };
        entity_registry_.view<shiva::ecs::transform_2d, shiva::ecs::physics_2d>().each(update_functor);
        this->world_.Step(this->fixed_delta_time_, 6, 2);
    }

    //! Reflection
    constexpr auto box2d_system::reflected_functions() noexcept
    {
        return meta::makeMap();
    }

    constexpr auto box2d_system::reflected_members() noexcept
    {
        return meta::makeMap();
    }

    void box2d_system::on_set_user_data_() noexcept
    {
        state_ = static_cast<sol::state *>(user_data_);
        assert(state_ != nullptr);
        shiva::lua::register_type<box2d_system>(*state_, log_);

        (*state_).new_enum<b2BodyType>("body_type",
                                       {
                                           {"dynamic",   b2BodyType::b2_dynamicBody},
                                           {"static",    b2BodyType::b2_staticBody},
                                           {"kinematic", b2BodyType::b2_kinematicBody}
                                       });

        (*state_)[box2d_system::class_name()]["add_physics"] = [this](box2d_system &self,
                                                                      shiva::entt::entity_registry::entity_type entity,
                                                                      b2BodyType body_type) {
            if (!entity_registry_.has<shiva::ecs::transform_2d>(entity))
                return;

            const auto &box = entity_registry_.get<shiva::ecs::transform_2d>(entity);

            b2BodyDef def;
            def.type = body_type;
            def.userData = &entity;

            const auto body = world_.CreateBody(&def);
            entity_registry_.assign<shiva::ecs::physics_2d>(entity,
                                                            std::make_shared<shiva::box2d::box2d_component>(body));
            b2PolygonShape shape;
            shape.SetAsBox(box.width / 30.f, box.height / 30.f);

            b2FixtureDef fixture_def;
            fixture_def.shape = &shape;
            fixture_def.density = 1.0f;
            fixture_def.friction = 1.0f;
            body->CreateFixture(&fixture_def);
            body->SetTransform(b2Vec2(box.y, box.x), body->GetAngle());
        };
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::box2d_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)

