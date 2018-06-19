set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/sfml/inputs)


set(MODULE_PUBLIC_SOURCES
        "${MODULE_PATH}/system-sfml-inputs.cpp"
        )

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/system-sfml-inputs.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_SOURCES}
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})