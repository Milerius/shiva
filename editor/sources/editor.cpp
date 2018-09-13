//
// Created by roman Sztergbaum on 30/08/2018.
//

#include <shiva/world/world_common_initializer.hpp>
#include "editor.hpp"

namespace shiva::editor
{
    void editor::receive(const shiva::event::after_system_reload_plugins &evt) noexcept
    {
        auto system_ptr = evt.system_raw_ptr;
        if (system_ptr->get_name() == "render_system") {
            auto resources_system = system_manager_.get_system_by_name("resources_system",
                                                                       shiva::ecs::system_type::pre_update);
            auto input_system = system_manager_.get_system_by_name("input_system",
                                                                   shiva::ecs::system_type::pre_update);
            auto video_system = system_manager_.get_system_by_name("video_system",
                                                                   shiva::ecs::system_type::logic_update);
            auto lua_system = system_manager_.get_system<shiva::scripting::lua_system>();
            shiva::ecs::opaque_data full_data;
            full_data.data_1 = &lua_system.get_state();
            full_data.data_2 = system_ptr->get_user_data();
            resources_system->set_user_data(&full_data);
            input_system->set_user_data(system_ptr->get_user_data());
            video_system->set_user_data(&full_data);
            system_ptr->set_user_data(&lua_system.get_state());
            system_manager_.get_system<shiva::editor::editor_gui>().load_editor_resources();
        }
    }

    editor::editor() noexcept
    {
        this->dispatcher_.sink<shiva::event::after_system_reload_plugins>().connect(this);
        bool res = shiva::common::sfml_initializer(this->system_manager_);
        assert(res);
        system_manager_.load_systems<shiva::editor::editor_gui>(window_cfg_,
                                                                system_manager_.get_system<shiva::scripting::lua_system>().get_state());
        system_manager_.prioritize_system(shiva::editor::editor_gui::class_name(), "render_system",
                                          shiva::ecs::system_type::post_update);
        system_manager_.prioritize_system("imgui_system", shiva::editor::editor_gui::class_name(),
                                          shiva::ecs::system_type::post_update);
    }
}
