include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(pybind11 CONFIG REQUIRED)

if (WIN32)
    ## We need pyton dll
    file(GLOB PYTHON_DLL ${PYTHON_LIBRARIES}/../*.dll)
    message("PYTHON LIBRARIES -> ${PYTHON_LIBRARIES}")
    message(STATUS "DLL TO COPY -> ${PYTHON_DLL}")
    file(COPY ${PYTHON_DLL} DESTINATION ${CMAKE_SOURCE_DIR}/bin)
endif ()

CREATE_MODULE(shiva::pyscripting "${MODULE_SOURCES}" ${MODULE_PATH})

target_link_libraries(pyscripting INTERFACE shiva::ecs pybind11::embed pybind11::module)

AUTO_TARGETS_MODULE_INSTALL(pyscripting)
