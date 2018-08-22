cmake_minimum_required(VERSION 3.12)
project(<project_name>)

set(CMAKE_CXX_STANDARD 17)

##! CMake Path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(library)

##! Shiva
find_package(shiva CONFIG REQUIRED)
find_package(shiva-sfml CONFIG REQUIRED)
find_package(shiva-box2d CONFIG REQUIRED)
find_package(shiva-imgui CONFIG REQUIRED)

##! Sources
file(GLOB_RECURSE <PROJECT_NAME>_SOURCES <project_name>/*.cpp prerequisites/*.cpp)
file(GLOB_RECURSE <PROJECT_NAME>_HEADERS <project_name>/*.hpp)

##! Executable
add_executable(<project_name> ${<PROJECT_NAME>_SOURCES} ${<PROJECT_NAME>_HEADERS})

##! Linking
##! We manualy link LUA_LIBRARIES on Windows,
##! CMake seems to have a bug on interfacing this libraries from the module shiva::lua
target_link_libraries(<project_name> PUBLIC
        shiva::shiva
        ${LUA_LIBRARIES})

set_target_properties(<project_name>
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
        PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        PDB_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
        PDB_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/sfml_config.json
        ${CMAKE_SOURCE_DIR}/bin/assets/cfg/sfml_config.json
        COPYONLY)