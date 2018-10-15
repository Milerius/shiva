//
// Created by roman Sztergbaum on 15/06/2018.
//

#include <fstream>
#include <iomanip>
#include <imgui.h>
#include <boost/dll.hpp>
#include <shiva/sfml/graphics/system-sfml-graphics.hpp>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/sfml/common/drawable_component_impl.hpp>
#include "system-sfml-graphics.hpp"

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
        this->dispatcher_.sink<shiva::event::key_pressed>().connect(this);
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
		sf::Time delta_time = sf::seconds(static_cast<float>(fixed_delta_time_));
        auto update_transform = []([[maybe_unused]] auto entity, auto &&transform, auto &&drawable) {
            auto transform_ptr = std::static_pointer_cast<shiva::sfml::drawable_component_impl>(
                drawable.drawable_)->transformable;
            if (transform_ptr != nullptr) {
                //! Angle
                if (transform_ptr->getScale() != sf::Vector2f(transform.scale_x, transform.scale_y)) {
                    transform_ptr->setScale(sf::Vector2f(transform.scale_x, transform.scale_y));
                    transform.width = transform.original_width * transform.scale_x;
                    transform.height = transform.original_height * transform.scale_y;
                }

                //! Rotation
                if (static_cast<unsigned int>(transform_ptr->getRotation()) !=
                    static_cast<unsigned int>(transform.angle)) {
                    transform_ptr->setRotation(transform.angle);
                    auto rect = transform_ptr->getTransform().transformRect(
                        sf::FloatRect(0.f, 0.f, transform.original_width,
                                      transform.original_height));
                    transform.width = rect.width;
                    transform.height = rect.height;
                    transform.x = rect.left;
                    transform.y = rect.top;
                } else {
                    //! Position
                    transform_ptr->setPosition(transform.x, transform.y);
                }
            }
        };

        auto draw = [this]([[maybe_unused]] auto entity, [[maybe_unused]] auto &&layer, auto &&drawable) {
            auto drawable_ptr = std::static_pointer_cast<shiva::sfml::drawable_component_impl>(drawable.drawable_);
            if (drawable_ptr != nullptr && drawable_ptr->drawable != nullptr) {
                this->win_.draw(*drawable_ptr->drawable);
                if (debug_draw_ &&
                    this->entity_registry_.has<shiva::ecs::transform_2d>(entity)) {
                    const auto &box = entity_registry_.get<shiva::ecs::transform_2d>(entity);
                    sf::RectangleShape shape_debug(sf::Vector2f(box.width, box.height));
                    //shape_debug.setRotation(box.angle);
                    shape_debug.setFillColor(sf::Color(0, 0, 0, 0));
                    shape_debug.setOutlineThickness(1.0f);
                    shape_debug.setOutlineColor(sf::Color::Red);
                    shape_debug.setPosition(box.x, box.y);
                    this->win_.draw(shape_debug);
                }
            }
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
                unsigned int style = sf::Style::Default;

                if (cfg_.borderless) {
                    style = sf::Style::None;
                } else if (cfg_.fullscreen) {
                    style = sf::Style::Fullscreen;
                }
                win_.create((!cfg_.native_resolution) ? sf::VideoMode{cfg_.size[0], cfg_.size[1]}
                                                      : sf::VideoMode{sf::VideoMode::getDesktopMode()}, cfg_.name,
                            style);

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

                if (cfg_.native_resolution) {
                    cfg_.size[0] = sf::VideoMode::getDesktopMode().width;
                    cfg_.size[1] = sf::VideoMode::getDesktopMode().height;
                }
                this->dispatcher_.trigger<shiva::event::window_config_update>(
                    std::make_tuple(cfg_.name, cfg_.size, cfg_.vsync, cfg_.fullscreen, cfg_.native_resolution));
                i.close();
            }
        }
        ImGui::SFML::Init(win_);
    }

    //! Callbacks
    void render_system::receive(const shiva::event::key_pressed &evt)
    {
        if (evt.keycode == shiva::input::keyboard::Key::F2) {
            debug_draw_ = !debug_draw_;
        }
    }

    void render_system::on_set_user_data_() noexcept
    {
        state_ = static_cast<sol::state *>(user_data_);
        assert(state_);
        shiva::lua::register_type<render_system>(*state_, log_);
        (*state_)[render_system::class_name()]["imgui_image_button"] = []([[maybe_unused]] render_system &self,
                                                                          const char *texture_id) {
            //toto
            sol::table table = (*self.state_)["shiva"]["resource_registry"];
            const sf::Texture &texture = table["get_texture_c"](table, texture_id);
            return ImGui::ImageButton(texture);
        };

        (*state_)[render_system::class_name()]["get_texture_size"] = []([[maybe_unused]] render_system &self,
                                                                        const char *texture_id) {
            sol::table table = (*self.state_)["shiva"]["resource_registry"];
            const sf::Texture &texture = table["get_texture_c"](table, texture_id);
            return std::make_pair(texture.getSize().x, texture.getSize().y);
        };

            (*state_)[render_system::class_name()]["update_font"] = [this]([[maybe_unused]] render_system &self) {
                this->log_->debug("updating fonts");
                ImGui::SFML::UpdateFontTexture();
            };

        (*state_)["shiva"]["render"] = this;
    }
}

BOOST_DLL_ALIAS(
    shiva::plugins::render_system::system_creator, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)
