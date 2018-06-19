//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <signal.h>
#include <string>
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
        static void handler(int signum)
        {
            std::cerr << "received: " << signum << std::endl;
            std::cerr << shiva::bs::stacktrace() << std::endl;
            shiva::bs::safe_dump_to((shiva::fs::temp_directory_path() /= "backtrace.dump").string().c_str());
            ::raise(SIGABRT);
        }
        void receive(const shiva::event::fatal_error_occured &evt)
        {
            using namespace std::string_literals;
            entity_registry_.each([this](const shiva::entt::entity_registry::entity_type entity) {
                this->entity_registry_.destroy(entity);
            });
            dispatcher_.trigger<shiva::event::quit_game>(evt.ec_.value());
            std::cerr << shiva::bs::stacktrace() << std::endl;
            shiva::bs::safe_dump_to(backtrace_path_.string().c_str());
            throw std::logic_error("fatal_error_occured: "s + evt.ec_.message());
        }

        general_handler(entt::dispatcher &dispatcher, entt::entity_registry &entity_registry) noexcept :
            dispatcher_(dispatcher),
            entity_registry_(entity_registry)
        {
            this->dispatcher_.sink<shiva::event::fatal_error_occured>().connect(this);
            signal(SIGSEGV, general_handler::handler);
            if (shiva::fs::exists(backtrace_path_)) {
                std::ifstream ifs(backtrace_path_.string());
                shiva::bs::stacktrace st = shiva::bs::stacktrace::from_dump(ifs);
                std::cerr << "Previous run crashed:\n" << st << std::endl;
                ifs.close();
                shiva::fs::remove(backtrace_path_);
            }
        }

    private:
        entt::dispatcher &dispatcher_;
        entt::entity_registry &entity_registry_;
        shiva::fs::path backtrace_path_{shiva::fs::temp_directory_path() /= "backtrace.dump"};
    };
}
