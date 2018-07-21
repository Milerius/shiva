//
// Created by roman Sztergbaum on 19/07/2018.
//

#include <boost/dll.hpp>
#include <shiva/sfml/resources/system-sfml-resources.hpp>

namespace shiva::plugins
{
    std::unique_ptr<shiva::ecs::base_system>
    resources_system::system_creator(entt::dispatcher &dispatcher, entt::entity_registry &registry,
                                     const float &fixed_delta_time) noexcept
    {
        return std::make_unique<shiva::plugins::resources_system>(dispatcher, registry, fixed_delta_time);
    }

    void resources_system::update() noexcept
    {
       /* if (resources_registry_.is_working()) {
            auto& current_loaded = resources_registry_.get_nb_current_files_loaded_();
            auto& nb_files = resources_registry_.get_nb_files();
            progress_ = static_cast<float>(current_loaded) / nb_files;
            log_->info("loading files: {0} / {1}, percentage: {2}%",
                       current_loaded,
                       nb_files,
                       progress_ * 100);
        }*/
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::resources_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
