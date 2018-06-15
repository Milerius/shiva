set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/sfml/graphics)


set(MODULE_PUBLIC_SOURCES
        "${MODULE_PATH}/system-sfml-graphics.cpp"
        )

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/system-sfml-graphics.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_SOURCES}
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})