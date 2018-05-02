if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there")
endif ()

cmake_minimum_required(VERSION 3.9)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##! Project
project(rs_engine)

##! Prerequisites CTEST
enable_testing()

##! CMake Path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(library)

##! Project options
option(RS_ENGINE_BUILD_TESTS "Build tests of rs_engine C++ engine" ON)
option(RS_ENGINE_BUILD_EXAMPLES "Build examples of rs_engine C++ engine" OFF)

##! Project modules
add_subdirectory(modules)

##! Project tests
if (RS_ENGINE_BUILD_TESTS)
    add_subdirectory(tests)
endif ()

##! Project examples
if (RS_ENGINE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()