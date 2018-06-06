include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(shiva::reflection "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(shiva-reflection INTERFACE shiva::pp shiva::meta)