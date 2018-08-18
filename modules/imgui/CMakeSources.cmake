set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/imgui)


set(MODULE_PUBLIC_SOURCES
        "${MODULE_PATH}/system-imgui.cpp"
        "${MODULE_PATH}/imgui_lua_bindings.cpp"
        )

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/system-imgui.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_SOURCES}
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})