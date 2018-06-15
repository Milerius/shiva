include(CMakeSources.cmake)

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Boost COMPONENTS system filesystem REQUIRED)
CREATE_MODULE(shiva::filesystem "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(filesystem INTERFACE Boost::boost Boost::filesystem)

if (LINUX)
    target_link_libraries(filesystem INTERFACE stdc++fs)
endif(LINUX)

if(APPLE)
    target_link_libraries(filesystem INTERFACE /usr/local/opt/llvm/lib/libc++experimental.a)
endif(APPLE)

AUTO_TARGETS_MODULE_INSTALL(filesystem)