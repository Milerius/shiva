//
// Created by roman Sztergbaum on 15/08/2018.
//

#pragma once

#include <array>
#include <string>
#include <shiva/json/json.hpp>

namespace shiva::sfml
{
    struct window_config
    {
        std::string name{"sfml window"};
        std::array<unsigned int, 2> size{{1920, 1080}};
        bool vsync{false};
        bool fullscreen{false};
        bool native_resolution{false};
        bool borderless{false};
    };

    inline void to_json(shiva::json::json &j, const window_config &cfg)
    {
        j = shiva::json::json{{"name",              cfg.name},
                              {"size",              cfg.size},
                              {"vsync",             cfg.vsync},
                              {"fullscreen",        cfg.fullscreen},
                              {"native_resolution", cfg.native_resolution},
                              {"borderless",        cfg.borderless}};
    }

    inline void from_json(const shiva::json::json &j, window_config &cfg)
    {
        cfg.name = j.at("name").get<std::string>();
        cfg.size = j.at("size").get<std::array<unsigned int, 2>>();
        cfg.vsync = j.at("vsync").get<bool>();
        cfg.fullscreen = j.at("fullscreen").get<bool>();
        cfg.native_resolution = j.at("native_resolution").get<bool>();
        cfg.borderless = j.at("borderless").get<bool>();
    }
}