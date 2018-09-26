//
// Created by syl on 21/09/2018.
//

#pragma once

#include <ruby.h>

#include <shiva/reflection/reflection.hpp>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/ecs/system.hpp>

namespace shiva::ruby
{
    class ruby_system : public ecs::logic_update_system<ruby_system>
    {
    public:
        reflect_class(ruby_system)

    public:
        ruby_system(entt::dispatcher &dispatcher,
                    entt::entity_registry &entity_registry,
                    const float &fixed_delta_time,
                    shiva::fs::path scripts_directory = shiva::fs::current_path() / "assets/scripts/ruby",
                    shiva::fs::path systems_scripts_directory = shiva::fs::current_path() /
                                                                "assets/scripts/systems/ruby") noexcept :
          system(dispatcher, entity_registry, fixed_delta_time),
          scripts_directory_(scripts_directory),
          systems_scripts_directory_(systems_scripts_directory)
        {
          // Construct ruby VM
          ruby_init();

          log_->debug("ruby vm constructed.");
        }

        ~ruby_system() override
        {
          // Destruct ruby VM
          ruby_cleanup(0);

          log_->debug("ruby vm destroyed.");
        }

    public:
        void update() noexcept override
        {

        }

    private:
        shiva::fs::path scripts_directory_;
        shiva::fs::path systems_scripts_directory_;
    };
}