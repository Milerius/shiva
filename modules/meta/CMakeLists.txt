include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(shiva::meta "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(meta INTERFACE shiva::pp)
AUTO_TARGETS_MODULE_INSTALL(meta)

