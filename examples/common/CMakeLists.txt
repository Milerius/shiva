include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(shiva::examples "${MODULE_SOURCES}" ${MODULE_PATH})
