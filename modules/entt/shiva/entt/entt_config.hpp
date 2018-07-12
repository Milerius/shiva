//
// Created by roman Sztergbaum on 12/07/2018.
//

#pragma once

#include <shiva/pp/pp_export.hpp>
#include <entt/core/family.hpp>
#include <entt/config/config.h>
#include <entt/signal/dispatcher.hpp>
#include <entt/entity/registry.hpp>

namespace entt
{
    template
    class PP_API_EXPORT Family<struct InternalDispatcherEventFamily>;

    template
    class PP_API_EXPORT Family<struct InternalEmitterHandlerFamily>;

    template
    class PP_API_EXPORT Family<struct InternalRegistryTagFamily>;

    template
    class PP_API_EXPORT Family<struct InternalRegistryComponentFamily>;

    template
    class PP_API_EXPORT Family<struct InternalRegistryHandlerFamily>;
}