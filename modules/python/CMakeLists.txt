include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(pybind11 CONFIG REQUIRED)


if (WIN32)
    ## We need pyton dll
    file(GLOB PYTHON_DLL ${PYTHON_LIBRARIES}/../*.dll)

    get_filename_component(PARENT_DIR ${PYTHON_LIBRARIES} DIRECTORY)
    get_filename_component(PARENT_DIR ${PARENT_DIR} DIRECTORY)
    file(GLOB PYTHON_DLL ${PARENT_DIR}/*.dll)
    message("PYTHON LIBRARIES -> ${PYTHON_LIBRARIES}")
    message("PARENT -> ${PARENT_DIR}")
    message(STATUS "DLL TO COPY -> ${PYTHON_DLL}")
    file(COPY ${PYTHON_DLL} DESTINATION ${CMAKE_SOURCE_DIR}/bin)
endif ()

CREATE_MODULE(shiva::pyscripting "${MODULE_SOURCES}" ${MODULE_PATH} "python")

target_link_libraries(pyscripting INTERFACE shiva::ecs shiva::input pybind11::embed pybind11::module)
target_compile_options(pyscripting INTERFACE $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/bigobj>
        INTERFACE $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/bigobj>)
AUTO_TARGETS_MODULE_INSTALL(pyscripting)
