include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

CREATE_MODULE(shiva::shiva-spdlog "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(shiva-spdlog INTERFACE spdlog)

#find_path(ENTT_INCLUDE_DIR entt/entt.hpp)
#MSG_YELLOW_BOLD(STATUS "ENTT_INCLUDE_DIR: " "${ENTT_INCLUDE_DIR}" "")
#target_include_directories(entt INTERFACE ${ENTT_INCLUDE_DIR})

AUTO_TARGETS_MODULE_INSTALL(shiva-spdlog)
