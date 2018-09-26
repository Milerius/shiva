set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/ruby)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/ruby_system.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})