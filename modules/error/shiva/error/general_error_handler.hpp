//
// Created by roman Sztergbaum on 08/06/2018.
//

#pragma once

#include <csignal>
#include <string>
#include <iostream>
#include <fstream>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/stacktrace/stacktrace.hpp>
#include <shiva/entt/entt_config.hpp>

namespace shiva::error
{
    class general_handler
    {
    public:
        [[noreturn]] static void handler(int signum)
        {
            std::cerr << "received: " << signum << std::endl;
#if !defined(__EMSCRIPTEN__)
            std::cerr << shiva::bs::stacktrace() << std::endl;
            shiva::bs::safe_dump_to((shiva::fs::temp_directory_path() /= "backtrace.dump").string().c_str());
#endif
            std::terminate();
        }

        [[noreturn]] void receive(const shiva::event::fatal_error_occured &evt)
        {
            using namespace std::string_literals;
            entity_registry_.each([this](const shiva::entt::entity_registry::entity_type entity) {
                this->entity_registry_.destroy(entity);
            });
            dispatcher_.trigger<shiva::event::quit_game>(evt.ec_.value());
#if !defined(__EMSCRIPTEN__)
            if (auto &&bs = shiva::bs::stacktrace()) {
                log_->critical("backtrace:\n {}", shiva::bs::detail::to_string(&bs.as_vector()[0], bs.size()));
                shiva::bs::safe_dump_to(backtrace_path_.string().c_str());
            }
#endif
            throw std::logic_error("fatal_error_occured: "s + evt.ec_.message());
        }

        general_handler(entt::dispatcher &dispatcher, entt::entity_registry &entity_registry) noexcept :
            dispatcher_(dispatcher),
            entity_registry_(entity_registry)
        {
            shiva::entt::init_library(entity_registry_, dispatcher_);
            this->dispatcher_.sink<shiva::event::fatal_error_occured>().connect(this);
            signal(SIGSEGV, general_handler::handler);
#if !defined(__EMSCRIPTEN__)
            if (shiva::fs::exists(backtrace_path_)) {
                std::ifstream ifs(backtrace_path_.string());
                shiva::bs::stacktrace st = shiva::bs::stacktrace::from_dump(ifs);
                if (st) {
                    log_->warn("previous run crashed:\n {}",
                               shiva::bs::detail::to_string(&st.as_vector()[0], st.size()));
                }
                ifs.close();
                shiva::fs::remove(backtrace_path_);
            }
#endif
        }

    private:
        shiva::logging::logger log_{shiva::log::stdout_color_mt("general_error_handler")};
        entt::dispatcher &dispatcher_;
        entt::entity_registry &entity_registry_;
        shiva::fs::path backtrace_path_{shiva::fs::temp_directory_path() /= "backtrace.dump"};
    };
}
