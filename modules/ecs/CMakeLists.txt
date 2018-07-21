include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

##! ENTT
CREATE_MODULE(shiva::ecs "${MODULE_SOURCES}" ${MODULE_PATH})
target_include_directories(ecs INTERFACE ${ENTT_INCLUDE_DIR})
target_link_libraries(ecs INTERFACE
        shiva::reflection
        shiva::error
        shiva::event
        shiva::entt
        shiva::range
        shiva::dll
        shiva::timer
        shiva::shiva-spdlog)
target_compile_options(ecs INTERFACE $<$<PLATFORM_ID:Linux>:-Wno-attributes>)

AUTO_TARGETS_MODULE_INSTALL(ecs)
