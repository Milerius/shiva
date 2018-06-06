### Sources for the meta module

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shiva/meta)

set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/List.hpp
        ${MODULE_PATH}/PriorityTag.hpp
        ${MODULE_PATH}/Visitor.hpp
        ${MODULE_PATH}/TypeTraits.hpp
        ${MODULE_PATH}/TupleForEach.hpp
        ${MODULE_PATH}/Map.hpp
        ${MODULE_PATH}/Meta.hpp
        )

set(MODULE_PRIVATE_HEADERS "")

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
