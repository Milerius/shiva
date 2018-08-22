set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/ecs)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/system.hpp"
        "${MODULE_PATH}/system_type.hpp"
        "${MODULE_PATH}/system_manager.hpp"
        "${MODULE_PATH}/ecs.hpp"
        "${MODULE_PATH}/base_system.hpp"
        "${MODULE_PATH}/opaque_data.hpp"
        "${MODULE_PATH}/components/all.hpp"
        "${MODULE_PATH}/components/video.hpp"
        "${MODULE_PATH}/components/layer.hpp"
        "${MODULE_PATH}/components/lua_script.hpp"
        "${MODULE_PATH}/components/transform_2d.hpp"
        "${MODULE_PATH}/components/drawable.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "${MODULE_PATH}/details/system_type_traits.hpp"
        )

set(MODULE_SOURCES
        "${MODULE_PUBLIC_HEADERS}"
        "${MODULE_PRIVATE_HEADERS}"
        )

if (WIN32)
    set(SHIVA_WIN32_ECS_PUBLIC_MODULE_SOURCES "${MODULE_PUBLIC_HEADERS}" CACHE INTERNAL "" FORCE)
    set(SHIVA_WIN32_ECS_PRIVATE_MODULE_SOURCES "${MODULE_PRIVATE_HEADERS}" CACHE INTERNAL "" FORCE)
endif ()