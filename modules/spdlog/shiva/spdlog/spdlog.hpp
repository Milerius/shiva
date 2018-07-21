//
// Created by roman Sztergbaum on 19/06/2018.
//

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace shiva
{
    namespace log = spdlog;
}

namespace shiva::logging
{
    using logger = std::shared_ptr<shiva::log::logger>;
}
