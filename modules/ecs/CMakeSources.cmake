set(MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/shiva/ecs)

set(MODULE_PUBLIC_HEADERS
        "${MODULE_PATH}/system.hpp"
        "${MODULE_PATH}/using_alias_library.hpp"
        "${MODULE_PATH}/system_type.hpp"
        "${MODULE_PATH}/system_manager.hpp"
        "${MODULE_PATH}/ecs.hpp"
        "${MODULE_PATH}/base_system.hpp"

        )

set(MODULE_PRIVATE_HEADERS
        "${MODULE_PATH}/details/system_type_traits.hpp"
        "${MODULE_PATH}/details/utils.hpp")

set(MODULE_SOURCES
        ${MODULE_PUBLIC_HEADERS}
        ${MODULE_PRIVATE_HEADERS})