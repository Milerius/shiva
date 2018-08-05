set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/sfml/common)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/animation_component_impl.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})