include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

CREATE_MODULE(shiva::dll "${MODULE_SOURCES}" ${MODULE_PATH})

find_package(Boost COMPONENTS system filesystem REQUIRED)

target_link_libraries(dll INTERFACE Boost::boost ${CMAKE_DL_LIBS} shiva::filesystem Boost::filesystem)

AUTO_TARGETS_MODULE_INSTALL(dll)
