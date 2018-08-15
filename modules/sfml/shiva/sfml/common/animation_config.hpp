//
// Created by roman Sztergbaum on 15/08/2018.
//

#pragma once

#include <string>
#include <shiva/json/json.hpp>
#include "animation_component_impl.hpp"

namespace shiva::sfml
{
    struct animation_config
    {
        using status_t = animation_component_impl::status;
        status_t status{status_t::paused};
        float speed{0.0f};
        bool loop{false};
        int repeat{0};
        unsigned int columns{0};
        unsigned int lines{0};
        unsigned int nb_anims{0};
        std::string texture{"none"};
    };

    inline void to_json(shiva::json::json &j, const animation_config &cfg)
    {
        j = shiva::json::json{{"status",   cfg.status.toString()},
                              {"speed",    cfg.speed},
                              {"loop",     cfg.loop},
                              {"repeat",   cfg.repeat},
                              {"nb_columns",  cfg.columns},
                              {"nb_lines",    cfg.lines},
                              {"nb_anims", cfg.nb_anims},
                              {"texture",  cfg.texture}};
    }

    inline void from_json(const shiva::json::json &j, animation_config &cfg)
    {
        cfg.status = std::string_view(j.at("status").get<std::string>().c_str());
        cfg.speed = j.at("speed").get<float>();
        cfg.loop = j.at("loop").get<bool>();
        cfg.repeat = j.at("repeat").get<int>();
        cfg.columns = j.at("nb_columns").get<unsigned int>();
        cfg.lines = j.at("nb_lines").get<unsigned int>();
        cfg.nb_anims = j.at("nb_anims");
        cfg.texture = j.at("texture").get<std::string>();
    }
}