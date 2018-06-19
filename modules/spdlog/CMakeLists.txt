include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Threads REQUIRED)
CREATE_MODULE(shiva::shiva-spdlog "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(shiva-spdlog INTERFACE spdlog Threads::Threads)

AUTO_TARGETS_MODULE_INSTALL(shiva-spdlog)
