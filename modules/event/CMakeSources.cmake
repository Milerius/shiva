set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/event)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/add_base_system.hpp"
        "${MODULE_PATH}/fatal_error_occured.hpp"
        "${MODULE_PATH}/quit_game.hpp"
        "${MODULE_PATH}/start_game.hpp"
        "${MODULE_PATH}/after_load_systems_plugins.hpp"
        "${MODULE_PATH}/all.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})