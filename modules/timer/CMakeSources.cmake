### Sources for the pp module

set(MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/shiva/timer)
set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/timer.hpp
        ${MODULE_PATH}/timestep.hpp
        ${MODULE_PATH}/fps.hpp
        )

set(MODULE_PRIVATE_HEADERS "")

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
