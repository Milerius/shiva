//
// Created by roman Sztergbaum on 21/06/2018.
//

#pragma once

#if defined(fmt)
#undef fmt
#include <sol/state.hpp>
#else
#include <sol/state.hpp>
#endif
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/ecs/system.hpp>
#include <shiva/event/add_base_system.hpp>
#include <shiva/input/input.hpp>
#include <shiva/lua/lua_helpers.hpp>
#include <shiva/lua/details/lua_scripted_system.hpp>

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
        //! Private member functions
        template <typename Component>
        void register_component_() noexcept;

        template <typename Event>
        void register_event_() noexcept;

        inline void register_entity_registry_() noexcept;

        template <typename ... Types>
        void register_components_(meta::type_list<Types...>) noexcept;

        template <typename ... Types>
        void register_events_(meta::type_list<Types...>) noexcept;

        inline void register_world_() noexcept;

    public:
        //! Constructors
        inline lua_system(entt::dispatcher &dispatcher,
                          entt::entity_registry &entity_registry,
                          const float &fixed_delta_time,
                          shiva::fs::path scripts_directory = shiva::fs::current_path() / "assets/scripts/lua",
                          shiva::fs::path systems_scripts_directory = shiva::fs::current_path() /
                                                                      "assets/scripts/systems/lua") noexcept;

        //! Public member functions
        inline bool load_script(const std::string &file_name, const fs::path &script_directory) noexcept;

        inline bool load_script(const std::string &file_name) noexcept;

        inline bool load_script_from_entities() noexcept;

        template <typename ...Types>
        void register_types_list(meta::type_list<Types...>) noexcept;

        inline void update() noexcept override;

        inline bool create_scripted_system(const shiva::fs::path &script_name);

        inline bool load_all_scripted_systems() noexcept;

        inline sol::state &get_state() noexcept;

        //! Reflection
        reflect_class(lua_system)

        static inline constexpr auto reflected_functions() noexcept;

        static inline constexpr auto reflected_members() noexcept;

    private:
        template <typename ...Args>
        void execute_safe_function_(const std::string &table_name, std::string function_name, Args &&...args)
        {
            try {
                sol::optional<sol::function> f = (*state_)[table_name][std::move(function_name)];
                if (f) {
                    f.value()(std::forward<Args>(args)...);
                }
            }
            catch (const std::exception &error) {
                this->log_->error("lua error: {}", error.what());
            }
        }

        std::shared_ptr<sol::state> state_{std::make_shared<sol::state>()};
        shiva::fs::path script_directory_;
        shiva::fs::path systems_scripts_directory_;
    };
}

namespace shiva::scripting
{
    //! Private member functions
    template <typename Component>
    void lua_system::register_component_() noexcept
    {
        using namespace std::string_literals;
        log_->info("register component: {}", Component::class_name());

        (*state_)[entity_registry_.class_name()][Component::class_name() + "_id"] = [](
            shiva::entt::entity_registry &self) {
            return self.type<Component>();
        };

        (*state_)[entity_registry_.class_name()]["for_each_entities_which_have_" + Component::class_name() +
                                                 "_component"] = [](
            shiva::entt::entity_registry &self, sol::function functor) {
            self.view<Component>().each(functor);
        };

        (*state_)[entity_registry_.class_name()]["get_"s + Component::class_name() + "_component"s] = [](
            shiva::entt::entity_registry &self,
            shiva::entt::entity_registry::entity_type entity) {
            return std::ref(self.get<Component>(entity));
        };

        (*state_)[entity_registry_.class_name()]["has_"s + Component::class_name() + "_component"s] = [](
            shiva::entt::entity_registry &self,
            shiva::entt::entity_registry::entity_type entity) {
            return self.has<Component>(entity);
        };

        (*state_)[entity_registry_.class_name()]["remove_"s + Component::class_name() + "_component"s] = [](
            shiva::entt::entity_registry &self,
            shiva::entt::entity_registry::entity_type entity) {
            self.remove<Component>(entity);
        };

        if constexpr (std::is_default_constructible_v<Component>) {
            (*state_)[entity_registry_.class_name()]["add_"s + Component::class_name() + "_component"s] = [](
                shiva::entt::entity_registry &self,
                shiva::entt::entity_registry::entity_type entity) {
                return std::ref(self.assign<Component>(entity));
            };
        }
    }

    template <typename Event>
    void lua_system::register_event_() noexcept
    {
        using namespace std::string_literals;

        if constexpr (std::is_default_constructible_v<Event> && shiva::refl::has_constructor_arg_type_v<Event>) {
            (*state_)["dispatcher"]["trigger_"s + Event::class_name() + "_event"s] = Event::invoker;
        } else {
            (*state_)["dispatcher"]["trigger_"s + Event::class_name() + "_event"s] = [](
                shiva::entt::dispatcher &self) {
                return self.trigger<Event>();
            };
        }
    }

    void lua_system::register_entity_registry_() noexcept
    {
        shiva::lua::register_type<shiva::entt::entity_registry>(*state_, log_);
        using comp_type = shiva::entt::entity_registry::component_type;
        (*state_)[entity_registry_.class_name()]["for_each_runtime"] = [](shiva::entt::entity_registry &self,
                                                                          std::vector<comp_type> array,
                                                                          sol::function functor) {
            return self.view(std::cbegin(array), std::cend(array)).each([func = std::move(functor)](auto entity) {
                func(entity);
            });
        };

        (*state_)[entity_registry_.class_name()]["nb_entities"] = [](shiva::entt::entity_registry &self) {
            return self.size();
        };
    }

    template <typename... Types>
    void lua_system::register_components_(meta::type_list<Types...>) noexcept
    {
        (shiva::lua::register_type<Types>(*state_, log_), ...);
        (register_component_<Types>(), ...);
    }

    template <typename... Types>
    void lua_system::register_events_(meta::type_list<Types...>) noexcept
    {
        (shiva::lua::register_type<Types>(*state_, log_), ...);
        (register_event_<Types>(), ...);
    }

    void lua_system::register_world_() noexcept
    {
        (*state_)[entity_registry_.class_name()]["create_scripted_game_object"] = [this](
            shiva::entt::entity_registry &self, std::string script_name, std::string table_name) {
            auto entity_id = self.create();
            self.assign<shiva::ecs::lua_script>(entity_id, script_name, table_name);
            bool res = this->load_script(script_name);
            if (res) {
                execute_safe_function_(table_name, "on_init", entity_id);
            }
            return entity_id;
        };
        (*state_)["shiva"] = state_->create_table_with("entity_registry", std::ref(entity_registry_),
                                                       "dispatcher", std::ref(dispatcher_),
                                                       "fixed_delta_time", fixed_delta_time_);
    }

    //! Constructors
    lua_system::lua_system(entt::dispatcher &dispatcher, entt::entity_registry &entity_registry,
                           const float &fixed_delta_time, std::experimental::filesystem::path scripts_directory,
                           std::experimental::filesystem::path systems_scripts_directory) noexcept :
        system(dispatcher, entity_registry, fixed_delta_time),
        script_directory_(std::move(scripts_directory)),
        systems_scripts_directory_(std::move(systems_scripts_directory))
    {
        state_->open_libraries();
        state_->new_enum<shiva::ecs::system_type>("system_type",
                                                  {
                                                      {"pre_update",   shiva::ecs::system_type::pre_update},
                                                      {"post_update",  shiva::ecs::system_type::post_update},
                                                      {"logic_update", shiva::ecs::system_type::logic_update}
                                                  });
        state_->new_enum<shiva::input::keyboard::TKey>("Keyboard", KEYBOARD_INIT_LIST);
        (*state_)["load_script"] = [this](std::string filename, std::string path) {
            return this->load_script(std::move(filename), fs::path(std::move(path)));
        };

        (*state_)["load_all_scripted_entities"] = [this]() {
            return this->load_script_from_entities();
        };
        register_entity_registry_();
        register_components_(shiva::ecs::common_components{});
        this->state_->new_usertype<shiva::entt::dispatcher>("dispatcher");
        register_events_(shiva::event::common_events_list{});
        register_world_();
    }

    //! Public member functions
    bool lua_system::load_script(const std::string &file_name, const fs::path &script_directory) noexcept
    {
        try {
            state_->script_file((script_directory / fs::path(file_name)).string());
            log_->info("successfully register script: {}", file_name);
        } catch (const std::exception &e) {
            log_->error("error when loading script {0}: {1}\n script_directory {2}", file_name,
                        e.what(), script_directory.string());
            return false;
        }
        return true;
    }

    bool lua_system::load_script(const std::string &file_name) noexcept
    {
        return load_script(file_name, script_directory_);
    }

    template <typename... Types>
    void lua_system::register_types_list(meta::type_list<Types...>) noexcept
    {
        (shiva::lua::register_type<Types>(*state_, log_), ...);
    }

    void lua_system::update() noexcept
    {
        this->entity_registry_.view<shiva::ecs::lua_script>().each([this](auto entity_id,
                                                                          auto &&comp) {
            execute_safe_function_(comp.table_name, "on_update", entity_id);
        });
    }

    bool lua_system::create_scripted_system(const shiva::fs::path &script_name)
    {
        bool res = load_script(script_name.filename().string(), systems_scripts_directory_);
        if (!res)
            return false;
        auto table_name = script_name.filename().stem().string() + "_table";
        log_->info("table: {}", table_name);
        shiva::ecs::system_type sys_type = (*state_)[table_name]["current_system_type"];
        log_->info("system_type: {}", sys_type);
        switch (sys_type) {
            case shiva::ecs::post_update:
                dispatcher_.trigger<shiva::event::add_base_system>(
                    std::make_unique<shiva::ecs::details::lua_post_scripted_system>(dispatcher_, entity_registry_,
                                                                                    fixed_delta_time_, state_,
                                                                                    table_name,
                                                                                    script_name.filename().stem().string()));
                break;
            case shiva::ecs::pre_update:
                dispatcher_.trigger<shiva::event::add_base_system>(
                    std::make_unique<shiva::ecs::details::lua_pre_scripted_system>(dispatcher_, entity_registry_,
                                                                                   fixed_delta_time_, state_,
                                                                                   table_name,
                                                                                   script_name.filename().stem().string()));
                break;
            case shiva::ecs::logic_update:
                dispatcher_.trigger<shiva::event::add_base_system>(
                    std::make_unique<shiva::ecs::details::lua_logic_scripted_system>(dispatcher_, entity_registry_,
                                                                                     fixed_delta_time_, state_,
                                                                                     table_name,
                                                                                     script_name.filename().stem().string()));
                break;
            case shiva::ecs::size:
                break;
            default:
                break;
        }
        return res;
    }

    inline bool lua_system::load_all_scripted_systems() noexcept
    {
        bool res = true;
        fs::recursive_directory_iterator endit;
        for (fs::recursive_directory_iterator it(systems_scripts_directory_); it != endit; ++it) {
            if (!fs::is_regular_file(*it)) {
                continue;
            }
            log_->info("path -> {}", it->path().string());
            res &= create_scripted_system(it->path());
        }
        return res;
    }

    sol::state &lua_system::get_state() noexcept
    {
        return *state_;
    }

    constexpr auto lua_system::reflected_functions() noexcept
    {
        return meta::makeMap(reflect_function(&lua_system::update));
    }

    constexpr auto lua_system::reflected_members() noexcept
    {
        return meta::makeMap();
    }

    inline bool lua_system::load_script_from_entities() noexcept
    {
        bool res = true;
        this->entity_registry_.view<shiva::ecs::lua_script>().each([this, &res]([[maybe_unused]] auto entity_id,
                                                                                auto &&comp) {
            res &= this->load_script(comp.script);
            if (res) {
                execute_safe_function_(comp.table_name, "on_init", entity_id);
            }
        });
        return res;
    }
}
