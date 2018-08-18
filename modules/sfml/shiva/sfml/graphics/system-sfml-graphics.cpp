//
// Created by roman Sztergbaum on 15/06/2018.
//

#include <imgui.h>
#include <fstream>
#include <boost/dll.hpp>
#include <shiva/sfml/graphics/system-sfml-graphics.hpp>
#include <shiva/filesystem/filesystem.hpp>

namespace shiva::plugins
{
    //! Destructor
    render_system::~render_system() noexcept
    {
        std::string cfg_str = (shiva::fs::current_path() / "assets/cfg/sfml_config.json").string();
        std::ofstream o(cfg_str, std::ofstream::trunc);
        if (o.is_open()) {
            shiva::json::json j;
            j = cfg_;
            o << std::setw(4) << j << std::endl;
            o.close();
        }
        ImGui::SFML::Shutdown();
    }

    //! Constructor
    render_system::render_system(shiva::entt::dispatcher &dispatcher, shiva::entt::entity_registry &registry,
                                 const float &fixed_delta_time) noexcept :
        system(dispatcher, registry, fixed_delta_time, true)
    {
        user_data_ = &win_;

        //! Json config
        reload_json_configuration_();
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
        ImGui::SFML::Render(win_);
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

    //! Private member functions
    void render_system::reload_json_configuration_() noexcept
    {
        std::string cfg_str = (shiva::fs::current_path() / "assets/cfg/sfml_config.json").string();
        shiva::json::json j;
        if (!shiva::fs::exists(cfg_str)) {
            std::error_code ec;
            shiva::fs::create_directories(shiva::fs::current_path() / "assets/cfg", ec);
            if (!ec) {
                log_->warn("create_directory fail -> {}", ec.message());
            }
            std::ofstream o(cfg_str);
            if (o.is_open()) {
                j = cfg_;
                o << std::setw(4) << j << std::endl;
                o.close();
            }
        } else {
            std::ifstream i(cfg_str);
            if (i.is_open()) {
                i >> j;
                cfg_ = j;
                win_.create(sf::VideoMode{cfg_.size[0], cfg_.size[1]}, cfg_.name,
                            (cfg_.fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
                win_.setVerticalSyncEnabled(cfg_.vsync);
                if (!cfg_.vsync) {
                    win_.setFramerateLimit(60);
                }
                ImGui::SFML::Init(win_);
                i.close();
            }
        }
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::render_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
