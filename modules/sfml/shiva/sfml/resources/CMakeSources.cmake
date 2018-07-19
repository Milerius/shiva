set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/sfml/resources)


set(MODULE_PUBLIC_SOURCES
        "${MODULE_PATH}/system-sfml-resources.cpp"
        )

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/system-sfml-resources.hpp"
        "${MODULE_PATH}/sfml-resources-registry.hpp"
        "${MODULE_PATH}/entt-sfml-loader.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_SOURCES}
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})