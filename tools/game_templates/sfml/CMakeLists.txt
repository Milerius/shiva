cmake_minimum_required(VERSION 3.12)
project(<project_name>)

set(CMAKE_CXX_STANDARD 17)

##! Shiva
find_package(shiva CONFIG REQUIRED)
find_package(shiva-sfml CONFIG REQUIRED)

##! Sources
file(GLOB_RECURSE <PROJECT_NAME>_SOURCES <project_name>/*.cpp)
file(GLOB_RECURSE <PROJECT_NAME>_HEADERS <project_name>/*.hpp)

##! Executable
add_executable(<project_name> ${<PROJECT_NAME>_SOURCES} ${<PROJECT_NAME>_HEADERS})

##! Linking
target_link_libraries(<project_name>
        shiva::shiva)

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