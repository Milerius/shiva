//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <iostream>
#include <fstream>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/stacktrace/stacktrace.hpp>
#include <shiva/entt/entt.hpp>

namespace shiva::error
{
    class general_handler
    {
    public:
        void receive(const shiva::event::fatal_error_occured &evt)
        {
            entity_registry_.each([this](auto entity) {
                this->entity_registry_.destroy(entity);
            });
            dispatcher_.trigger<shiva::event::quit_game>(evt.ec_.value());
        }

        general_handler(entt::dispatcher &dispatcher, entt::entity_registry &entity_registry) noexcept :
            dispatcher_(dispatcher),
            entity_registry_(entity_registry)
        {
            this->dispatcher_.sink<shiva::event::fatal_error_occured>().connect(this);
            if (shiva::fs::exists("stacktrace/backtrace.dump")) {
                // there is a backtrace
                std::ifstream ifs("stacktrace/backtrace.dump");

                shiva::bs::stacktrace st = shiva::bs::stacktrace::from_dump(ifs);
                std::cerr << "Previous run crashed:\n" << st << std::endl;

                // cleaning up
                ifs.close();
                shiva::fs::remove("stacktrace/backtrace.dump");
            }
        }

    private:
        entt::dispatcher &dispatcher_;
        entt::entity_registry &entity_registry_;
    };
}
