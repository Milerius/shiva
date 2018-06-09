include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(range-v3 CONFIG REQUIRED)
CREATE_MODULE(shiva::range "${MODULE_SOURCES}" ${MODULE_PATH})

target_link_libraries(shiva-range INTERFACE meta range-v3)