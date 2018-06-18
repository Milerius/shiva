set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/event)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/fatal_error_occured.hpp"
        "${MODULE_PATH}/quit_game.hpp"
        "${MODULE_PATH}/start_game.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})