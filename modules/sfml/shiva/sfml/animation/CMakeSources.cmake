set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/sfml/animation)


set(MODULE_PUBLIC_SOURCES
        "${MODULE_PATH}/system-sfml-animation.cpp"
        )

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/system-sfml-animation.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_SOURCES}
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})