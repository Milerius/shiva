##! EnTT
include(shiva/entt/CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(shiva::entt "${MODULE_SOURCES}" ${MODULE_PATH})
find_path(ENTT_INCLUDE_DIR entt/entt.hpp)
MSG_YELLOW_BOLD(STATUS "ENTT_INCLUDE_DIR: " "${ENTT_INCLUDE_DIR}" "")
target_include_directories(entt INTERFACE ${ENTT_INCLUDE_DIR})
target_link_libraries(entt INTERFACE shiva::pp)
AUTO_TARGETS_MODULE_INSTALL(entt)

##! EnTT shared
include(shiva/entt_shared/CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE_PLUGIN(shiva::entt_shared "${MODULE_SOURCES}" ${MODULE_PATH} "" "entt_shared")
target_link_libraries(entt_shared PRIVATE shiva::meta shiva::event)
set_target_properties(entt_shared PROPERTIES CXX_VISIBILITY_PRESET hidden)
