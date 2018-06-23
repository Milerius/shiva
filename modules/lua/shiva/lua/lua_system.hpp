//
// Created by roman Sztergbaum on 21/06/2018.
//

#pragma once

#include <sol/state.hpp>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/event/add_base_system.hpp>
#include "scripted_system.hpp"

namespace sol
{
    template <>
    struct is_automagical<shiva::entt::entity_registry> : std::false_type
    {
    };
}

namespace shiva::scripting
{
    class lua_system : public shiva::ecs::logic_update_system<lua_system>
    {
    private:
        template <typename Component>
        void register_component()
        {
            using namespace std::string_literals;
            log_->info("register component: {}", Component::class_name());

            state_[entity_registry_.class_name()]["get_"s + Component::class_name() + "_component"s] = [](
                shiva::entt::entity_registry &self,
                shiva::entt::entity_registry::entity_type entity) {
                return std::ref(self.get<Component>(entity));
            };

            state_[entity_registry_.class_name()]["has_"s + Component::class_name() + "_component"s] = [](
                shiva::entt::entity_registry &self,
                shiva::entt::entity_registry::entity_type entity) {
                return self.has<Component>(entity);
            };

            state_[entity_registry_.class_name()]["remove_"s + Component::class_name() + "_component"s] = [](
                shiva::entt::entity_registry &self,
                shiva::entt::entity_registry::entity_type entity) {
                self.remove<Component>(entity);
            };

            if constexpr (std::is_default_constructible_v<Component>) {
                state_[entity_registry_.class_name()]["add_"s + Component::class_name() + "_component"s] = [](
                    shiva::entt::entity_registry &self,
                    shiva::entt::entity_registry::entity_type entity) {
                    return std::ref(self.assign<Component>(entity));
                };
            }
        }

    public:
        lua_system(entt::dispatcher &dispatcher,
                   entt::entity_registry &entity_registry,
                   const float &fixed_delta_time,
                   shiva::fs::path scripts_directory = shiva::fs::current_path() / "scripts") noexcept :
            system(dispatcher, entity_registry, fixed_delta_time),
            script_directory_(std::move(scripts_directory))
        {
            state_.open_libraries();
            state_.new_enum<shiva::ecs::system_type>("system_type",
                                                     {
                                                         {"pre_update",   shiva::ecs::system_type::pre_update},
                                                         {"post_update",  shiva::ecs::system_type::post_update},
                                                         {"logic_update", shiva::ecs::system_type::logic_update}
                                                     });
            disable();
        }

        template <typename T>
        void register_type() noexcept
        {
            const auto table = std::tuple_cat(
                std::make_tuple(T::class_name()),
                T::reflected_functions(),
                T::reflected_members());

            try {
                std::apply(
                    [this](auto &&...params) {
                        this->state_.new_usertype<T>(std::forward<decltype(params)>(params)...);
                    }, table);
            }
            catch (const std::exception &error) {
                log_->error("error: {}", error.what());
                return;
            }

            log_->info("successfully registering type: {}", T::class_name());
        }

        void register_entity_registry() noexcept
        {
            register_type<shiva::entt::entity_registry>();
        }

        void register_world() noexcept
        {
            state_["shiva"] = state_.create_table_with("entity_registry", std::ref(entity_registry_),
                                                       "fixed_delta_time", fixed_delta_time_);
        }

        void load_script(const std::string &file_name) noexcept
        {
            try {
                state_.script_file((script_directory_ / fs::path(file_name)).string());
                log_->debug("successfully register script: {}", file_name);
            } catch (const std::exception &e) {
                log_->error("error when loading script {0}: {1}", file_name, e.what());
            }
        }

        template <typename ...Types>
        void register_types_list(meta::type_list<Types...>) noexcept
        {
            (register_type<Types>(), ...);
        }

        template <typename ... Types>
        void register_components(meta::type_list<Types...>)
        {
            (register_type<Types>(), ...);
            (register_component<Types>(), ...);
        }

        void update() noexcept override
        {
        }

        void create_scripted_system(const shiva::fs::path &script_name)
        {
            load_script(script_name.string());
            auto table_name = script_name.stem().string() + "_table";
            log_->info("table: {}", table_name);
            shiva::ecs::system_type sys_type = state_[table_name]["current_system_type"];
            log_->info("system_type: {}", sys_type);
            switch (sys_type) {
                case shiva::ecs::post_update:
                    dispatcher_.trigger<shiva::event::add_base_system>(
                        std::make_unique<shiva::ecs::post_scripted_system>(dispatcher_, entity_registry_,
                                                                           fixed_delta_time_, state_, table_name,
                                                                           script_name.stem()));
                    break;
                case shiva::ecs::pre_update:
                    dispatcher_.trigger<shiva::event::add_base_system>(
                        std::make_unique<shiva::ecs::pre_scripted_system>(dispatcher_, entity_registry_,
                                                                          fixed_delta_time_, state_, table_name,
                                                                          script_name.stem()));
                    break;
                case shiva::ecs::logic_update:
                    dispatcher_.trigger<shiva::event::add_base_system>(
                        std::make_unique<shiva::ecs::logic_scripted_system>(dispatcher_, entity_registry_,
                                                                            fixed_delta_time_, state_, table_name,
                                                                            script_name.stem()));
                    break;
                default:
                    break;
            }
        }

    public:
        sol::state &get_state() noexcept
        {
            return state_;
        }

    public:
        //! Reflection
        reflect_class(lua_system);

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap(reflect_function(&lua_system::update));
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

    private:
        sol::state state_;
        shiva::fs::path script_directory_;
        shiva::logging::logger log_{shiva::log::stdout_color_mt("lua_system")};
    };
}
