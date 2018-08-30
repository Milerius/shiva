set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/world)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/world.hpp"
        "${MODULE_PATH}/world_common_initializer.hpp"
        "${MODULE_PATH}/window_config.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})