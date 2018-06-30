set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/python)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/python.hpp"
        "${MODULE_PATH}/python_system.hpp"
        "${MODULE_PATH}/python_scripted_system.hpp"
        )

set(MODULE_PRIVATE_HEADERS
        "")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})