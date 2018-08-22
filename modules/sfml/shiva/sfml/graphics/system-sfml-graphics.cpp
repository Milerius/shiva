//
// Created by roman Sztergbaum on 15/06/2018.
//

#include <imgui.h>
#include <fstream>
#include <boost/dll.hpp>
#include <shiva/sfml/graphics/system-sfml-graphics.hpp>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/sfml/common/drawable_component_impl.hpp>

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
        auto update_transform = []([[maybe_unused]] auto entity, auto &&transform, auto &&drawable) {
            auto transform_ptr = std::static_pointer_cast<shiva::sfml::drawable_component_impl>(
                drawable.drawable_)->transformable;
            if (transform_ptr != nullptr) {
                transform_ptr->setPosition(transform.top, transform.left);
            }
        };

        auto draw = [this]([[maybe_unused]] auto entity, [[maybe_unused]] auto &&layer, auto &&drawable) {
            auto drawable_ptr = std::static_pointer_cast<shiva::sfml::drawable_component_impl>(drawable.drawable_);
            if (drawable_ptr != nullptr && drawable_ptr->drawable != nullptr)
                this->win_.draw(*drawable_ptr->drawable);
        };

        entity_registry_.view<shiva::ecs::transform_2d, shiva::ecs::drawable>().each(update_transform);
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

                //! Reset window
                win_.create((!cfg_.native_resolution) ? sf::VideoMode{cfg_.size[0], cfg_.size[1]}
                                                      : sf::VideoMode{sf::VideoMode::getDesktopMode()}, cfg_.name,
                            (cfg_.fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);

                //! VSync
                win_.setVerticalSyncEnabled(cfg_.vsync);

                //! Center Window
                int x = (sf::VideoMode::getDesktopMode().width / 2) - (win_.getSize().x / 2);
                int y = (sf::VideoMode::getDesktopMode().height / 2) - (win_.getSize().y / 2);
                win_.setPosition(sf::Vector2i(x, y));

                //! Frame Limit
                if (!cfg_.vsync) {
                    win_.setFramerateLimit(60);
                }
                i.close();
            }
        }
        ImGui::SFML::Init(win_);
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::render_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
