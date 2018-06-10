include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

##! ENTT

##! EASTL
find_library(EASTL_LIBRARY EASTL)
message(STATUS "${EASTL_LIBRARY}")

CREATE_MODULE(shiva::ecs "${MODULE_SOURCES}" ${MODULE_PATH})
target_include_directories(ecs INTERFACE ${ENTT_INCLUDE_DIR})
target_link_libraries(ecs INTERFACE ${EASTL_LIBRARY}
        shiva::reflection
        shiva::error
        shiva::event
        shiva::stacktrace
        shiva::entt
        shiva::range)

AUTO_TARGETS_MODULE_INSTALL(ecs)