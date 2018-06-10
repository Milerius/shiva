include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

##! ENTT
CREATE_MODULE(shiva::ecs "${MODULE_SOURCES}" ${MODULE_PATH})
target_include_directories(ecs INTERFACE ${ENTT_INCLUDE_DIR})
target_link_libraries(ecs INTERFACE
        shiva::reflection
        shiva::error
        shiva::event
        shiva::stacktrace
        shiva::entt
        shiva::range
        shiva::dll)

AUTO_TARGETS_MODULE_INSTALL(ecs)