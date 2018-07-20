include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Threads REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
#target_link_libraries(main PRIVATE spdlog::spdlog)
CREATE_MODULE(shiva::shiva-spdlog "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(shiva-spdlog INTERFACE spdlog::spdlog Threads::Threads fmt::fmt)

AUTO_TARGETS_MODULE_INSTALL(shiva-spdlog)
