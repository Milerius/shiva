include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

CREATE_MODULE(shiva::event "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(event INTERFACE shiva::ecs shiva::input)
AUTO_TARGETS_MODULE_INSTALL(event)
