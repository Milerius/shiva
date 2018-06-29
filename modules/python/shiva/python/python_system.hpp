//
// Created by roman Sztergbaum on 27/06/2018.
//

#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/ecs/system.hpp>

namespace py = pybind11;

namespace shiva::scripting
{
    PYBIND11_EMBEDDED_MODULE(shiva, module_)
    {
        static_cast<void>(module_);
    };

    class python_system : public shiva::ecs::logic_update_system<python_system>
    {
    private:
        template <typename Component>
        void register_component()
        {
            using namespace std::string_literals;
            log_->info("register component: {}", Component::class_name());

            auto type = module_.attr(
                "entity_registry").cast<py::class_<shiva::entt::entity_registry, ::entt::DefaultRegistry>>();

            type.def((Component::class_name() + "_id"s).c_str(), [](shiva::entt::entity_registry &self) {
                return self.type<Component>();
            }).def(("get_"s + Component::class_name() + "_component"s).c_str(), [](shiva::entt::entity_registry &self,
                                                                                   shiva::entt::entity_registry::entity_type entity) {
                return std::ref(self.get<Component>(entity));
            }).def(("has_"s + Component::class_name() + "_component"s).c_str(), [](shiva::entt::entity_registry &self,
                                                                                   shiva::entt::entity_registry::entity_type entity) {
                return self.has<Component>(entity);
            }).def(("remove_"s + Component::class_name() + "_component"s).c_str(),
                   [](shiva::entt::entity_registry &self,
                      shiva::entt::entity_registry::entity_type entity) {
                       return self.remove<Component>(entity);
                   }).def(("for_each_entities_which_have_"s + Component::class_name() +
                           "_component"s).c_str(),
                          [](shiva::entt::entity_registry &self,
                             py::object functor) {
                              auto view = self.view<Component>();
                              for (auto entity : view) {
                                  functor(entity);
                              }
                          });

            if constexpr (std::is_default_constructible_v<Component>) {
                type.def(("add_"s + Component::class_name() + "_component"s).c_str(),
                         [](shiva::entt::entity_registry &self,
                            shiva::entt::entity_registry::entity_type entity) {
                             return std::ref(self.assign<Component>(entity));
                         });
            }
        }

    public:
        python_system(entt::dispatcher &dispatcher,
                      entt::entity_registry &entity_registry,
                      const float &fixed_delta_time,
                      shiva::fs::path scripts_directory = shiva::fs::current_path() / "python_scripts",
                      shiva::fs::path systems_scripts_directory = shiva::fs::current_path() /
                                                                  fs::path("python_scripts")) noexcept :
            system(dispatcher, entity_registry, fixed_delta_time),
            script_directory_(std::move(scripts_directory)),
            systems_scripts_directory_(std::move(systems_scripts_directory))
        {
            globals_ = py::globals();
            py::enum_<shiva::ecs::system_type>(module_, "system_type")
                .value("pre_update", shiva::ecs::system_type::pre_update)
                .value("logic_update", shiva::ecs::system_type::logic_update)
                .value("post_update", shiva::ecs::system_type::post_update)
                .export_values();
            disable();
        }

        bool load_script(const std::string &file_name) noexcept
        {
            try {
                import_module(fs::path(file_name).stem().string(), (script_directory_ /= fs::path(file_name)).string(),
                              globals_);
            }
            catch (const std::exception &error) {
                log_->error("error -> {}", error.what());
                return false;
            }
            return true;
        }

        pybind11::module &get_module() noexcept
        {
            return module_;
        }

        const pybind11::module &get_module() const noexcept
        {
            return module_;
        }

        template <typename T>
        decltype(auto) register_type() noexcept
        {
            if constexpr (shiva::refl::has_base_class_v<T>) {
                py::class_<T, typename T::base_class_t> type(module_, T::class_name().c_str(), py::dynamic_attr());
                register_type_epilogue<T>(type);
                return type;
            } else {
                py::class_<T> type(module_, T::class_name().c_str(), py::dynamic_attr());
                register_type_epilogue<T>(type);
                return type;
            }
        }

        void register_entity_registry() noexcept
        {
            py::class_<::entt::DefaultRegistry> base_type(module_, "DefaultRegistry", py::dynamic_attr());
            auto type = register_type<shiva::entt::entity_registry>();
            type.def("nb_entities", [](shiva::entt::entity_registry &self) {
                return self.size();
            });
            module_.attr("ett_registry") = &entity_registry_;
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

    private:
        template <typename T, typename ClassType>
        void register_type_epilogue(ClassType &&type)
        {
            shiva::meta::for_each(T::reflected_functions(), [&type](auto &&name, auto &&func) {
                type.def(name.data(), func);
            });

            shiva::meta::for_each(T::reflected_members(), [&type](auto &&name, auto &&var) {
                using member_type = std::remove_reference_t<decltype(std::declval<T>().*(var))>;
                if constexpr (std::is_const_v<member_type>)
                    type.def_readonly(name.data(), var);
                else
                    type.def_readwrite(name.data(), var);
            });

            log_->info("successfully registering type: {}", T::class_name());
        }

        py::object import_module(const std::string &module, const std::string &path, py::object &globals)
        {
            py::dict locals;
            locals["module_name"] = py::cast(module);
            locals["path"] = py::cast(path);

            const char *expression = "import imp\n"
                                     "new_module = imp.load_module(module_name, open(path), path, ('py', 'U', imp.PY_SOURCE))\n";
            py::eval<py::eval_statements>(
                expression,
                globals,
                locals);

            module_.add_object(module.c_str(), locals["new_module"]);
            return locals["new_module"];
        }

    public:
        reflect_class(python_system);

        static constexpr auto reflected_functions() noexcept
        {
            return meta::makeMap(reflect_function(&python_system::update));
        }

        static constexpr auto reflected_members() noexcept
        {
            return meta::makeMap();
        }

    private:
        py::scoped_interpreter guard_;
        py::dict globals_;
        py::dict locals_;
        py::module module_{py::module::import("shiva")};
        shiva::fs::path script_directory_;
        shiva::fs::path systems_scripts_directory_;
        shiva::logging::logger log_{shiva::log::stdout_color_mt("python_system")};
    };
}