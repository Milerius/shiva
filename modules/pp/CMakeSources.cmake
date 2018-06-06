### Sources for the pp module

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shiva/pp)
set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/pp_paste.hpp
        ${MODULE_PATH}/pp_stringify.hpp
        ${MODULE_PATH}/pp_count_args.hpp
        ${MODULE_PATH}/pp_first_arg.hpp
        ${MODULE_PATH}/pp_for_each.hpp
        ${MODULE_PATH}/PP.hpp
        )

set(MODULE_PRIVATE_HEADERS
        ${MODULE_PATH}/details/pp_for_each.hpp
        )

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
