### Sources for the meta module

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shiva/meta)

set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/list.hpp
        ${MODULE_PATH}/priority_tag.hpp
        ${MODULE_PATH}/visitor.hpp
        ${MODULE_PATH}/type_traits.hpp
        ${MODULE_PATH}/tuple_for_each.hpp
        ${MODULE_PATH}/map.hpp
        ${MODULE_PATH}/meta.hpp
        ${MODULE_PATH}/crtp.hpp
        ${MODULE_PATH}/named_type.hpp
        ${MODULE_PATH}/named_type_impl.hpp
        ${MODULE_PATH}/underlying_functionalities.hpp
        )

set(MODULE_PRIVATE_HEADERS "")

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
