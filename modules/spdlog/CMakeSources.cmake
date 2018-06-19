set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/spdlog)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/spdlog.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})