include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

##! ENTT
find_path(ENTT_INCLUDE_DIR entt/entt.hpp)
MSG_YELLOW_BOLD(STATUS "ENTT_INCLUDE_DIR: " "${ENTT_INCLUDE_DIR}" "")

##! EASTL
find_library(EASTL_LIBRARY EASTL)
message(STATUS "${EASTL_LIBRARY}")

CREATE_MODULE(shiva::ecs "${MODULE_SOURCES}" ${MODULE_PATH})
target_include_directories(shiva-ecs INTERFACE ${ENTT_INCLUDE_DIR})
target_link_libraries(shiva-ecs INTERFACE ${EASTL_LIBRARY})
target_compile_features(shiva-ecs INTERFACE cxx_alias_templates)