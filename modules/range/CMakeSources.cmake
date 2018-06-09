set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/range)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/nanorange.hpp"
        "${MODULE_PATH}/range.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})