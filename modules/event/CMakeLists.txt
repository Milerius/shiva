include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_path(ENTT_INCLUDE_DIR entt/entt.hpp)
MSG_YELLOW_BOLD(STATUS "ENTT_INCLUDE_DIR: " "${ENTT_INCLUDE_DIR}" "")


CREATE_MODULE(shiva::event "${MODULE_SOURCES}" ${MODULE_PATH})
target_include_directories(shiva-event INTERFACE ${ENTT_INCLUDE_DIR})