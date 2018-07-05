include(CMakeSources.cmake)

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Boost COMPONENTS system REQUIRED)
CREATE_MODULE(shiva::filesystem "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(filesystem INTERFACE Boost::boost)

if (LINUX AND NOT EMSCRIPTEN)
    target_link_libraries(filesystem INTERFACE stdc++fs)
endif(LINUX AND NOT EMSCRIPTEN)

if(APPLE)
    target_link_libraries(filesystem INTERFACE c++experimental)
endif(APPLE)

if (EMSCRIPTEN)
    find_package(Boost COMPONENTS system filesystem REQUIRED)
    target_link_libraries(filesystem INTERFACE Boost::filesystem)
endif()

AUTO_TARGETS_MODULE_INSTALL(filesystem)
