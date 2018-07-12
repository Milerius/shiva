set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/entt)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/entt.hpp"
        "${MODULE_PATH}/entt_config.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})