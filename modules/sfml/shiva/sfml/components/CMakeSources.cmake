set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/sfml/components)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/sprite.hpp"
        "${MODULE_PATH}/components.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})