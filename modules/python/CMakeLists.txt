include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(pybind11 CONFIG REQUIRED)

CREATE_MODULE(shiva::pyscripting "${MODULE_SOURCES}" ${MODULE_PATH})

target_link_libraries(pyscripting INTERFACE shiva::ecs pybind11::embed pybind11::module)

AUTO_TARGETS_MODULE_INSTALL(pyscripting)
