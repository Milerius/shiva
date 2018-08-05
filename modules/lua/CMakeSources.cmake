set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/lua)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/lua.hpp"
        "${MODULE_PATH}/lua_system.hpp"
        "${MODULE_PATH}/lua_scripted_system.hpp"
        "${MODULE_PATH}/lua_helpers.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})