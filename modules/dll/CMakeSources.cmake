set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/dll)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/dll.hpp"
        "${MODULE_PATH}/plugins_registry.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})