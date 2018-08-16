set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/box2d)


set(MODULE_PUBLIC_SOURCES
        "${MODULE_PATH}/system-box2d.cpp"
        )

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/system-box2d.hpp"
        "${MODULE_PATH}/box2d_component.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_SOURCES}
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})