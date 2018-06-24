//
// Created by roman Sztergbaum on 19/06/2018.
//

#pragma once

#include <spdlog/spdlog.h>

namespace shiva
{
    namespace log = spdlog;
}

namespace shiva::logging
{
    using logger = std::shared_ptr<shiva::log::logger>;
}
