set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/systems/example_post_system.hpp"
        "${MODULE_PATH}/systems/example_pre_system.hpp"
        "${MODULE_PATH}/systems/all_systems.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})