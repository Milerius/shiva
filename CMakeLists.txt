if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there")
endif ()

cmake_minimum_required(VERSION 3.9)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##! Project
project(shiva)

##! Prerequisites CTEST
enable_testing()

##! CMake Path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(library)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML CONFIG COMPONENTS graphics window REQUIRED)

##! Project options
option(SHIVA_BUILD_TESTS "Build tests of shiva C++ engine" ON)
option(SHIVA_BUILD_EXAMPLES "Build examples of shiva C++ engine" OFF)

##! Project modules
add_subdirectory(modules)

##! Project tests
if (SHIVA_BUILD_TESTS)
    add_subdirectory(tests)
endif ()

##! Project examples
if (SHIVA_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()