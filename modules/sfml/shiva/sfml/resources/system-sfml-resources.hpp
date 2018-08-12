//
// Created by roman Sztergbaum on 19/07/2018.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/entt/entt_config.hpp>
#include <shiva/sfml/resources/sfml-resources-registry.hpp>
#include <shiva/lua/lua_helpers.hpp>

namespace shiva::plugins
{
    class resources_system final : public shiva::ecs::pre_update_system<resources_system>
    {
    public:
        //! Destructor
        ~resources_system() noexcept final = default;
        
        //! Constructor
        resources_system(shiva::entt::dispatcher &dispatcher,
                         shiva::entt::entity_registry &registry,
                         const float &fixed_delta_time) noexcept;

        //! Public static functions
        static std::unique_ptr<shiva::ecs::base_system> system_creator(entt::dispatcher &dispatcher,
                                                                       entt::entity_registry &registry,
                                                                       const float &fixed_delta_time) noexcept;
        //! Public member functions overriden
        void update() noexcept final;

        //! Reflection
        reflect_class(resources_system)

        static constexpr auto reflected_functions() noexcept;

        static constexpr auto reflected_members() noexcept;

    private:
        //! Private member functions overriden
        void on_set_user_data_() noexcept final;
        
        //! Private data members
        sfml::resources_registry resources_registry_;
        float progress_{0.0f};
        sol::state *state_{nullptr};
    };
}