set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/entt_shared)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/entt_shared.hpp"
        )


set(MODULE_PUBLIC_SOURCES
        "${MODULE_PATH}/entt_shared.cpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_SOURCES}
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})