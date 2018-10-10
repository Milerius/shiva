if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there")
endif ()

cmake_minimum_required(VERSION 3.9)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (WIN32)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif ()

##! Project
project(shiva VERSION 1.0)

##! Prerequisites CTEST
enable_testing()

##! Project options
option(SHIVA_BUILD_TESTS "Build tests of shiva C++ engine" OFF)
option(SHIVA_BUILD_EXAMPLES "Build examples of shiva C++ engine" OFF)
option(SHIVA_USE_BOX2D "Build shiva with box2d plugin" OFF)
option(SHIVA_USE_IMGUI "Build shiva with imgui plugin" OFF)
option(SHIVA_USE_SFML_AS_RENDERER "Build shiva with SFML rendering" OFF)
option(SHIVA_INSTALL_PLUGINS "Build shiva with SFML rendering" OFF)
option(DISABLE_INSTALL_SHIVA_CORE "Disable install main targets" OFF)
option(USE_PROJECT_IN_AN_IDE "Workaround for install header only library option, put it to ON if u use CLION" OFF)
option(SHIVA_BUILD_EDITOR "Shiva build editor" OFF)


##! CMake Path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(library)

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

if (SHIVA_BUILD_EDITOR AND SHIVA_USE_IMGUI)
    add_subdirectory(editor)
endif()

##! main library
add_library(shiva INTERFACE)

add_library(shiva::shiva ALIAS shiva)
target_link_libraries(shiva INTERFACE
        shiva::dll
        shiva::ecs
        shiva::entt
        shiva::enums
        shiva::error
        shiva::event
        shiva::filesystem
        shiva::input
        shiva::json
        shiva::lua
        shiva::meta
        shiva::pp
        shiva::pyscripting
        shiva::range
        shiva::reflection
        shiva::shiva-spdlog
        shiva::stacktrace
        shiva::timer
        shiva::world
        )

##! Install
if (NOT DISABLE_INSTALL_SHIVA_CORE)
    if (NOT USE_PROJECT_IN_AN_IDE AND NOT SHIVA_INSTALL_PLUGINS)
        include(GNUInstallDirs)

        include(CMakePackageConfigHelpers)

        write_basic_package_version_file(
                "${PROJECT_BINARY_DIR}/shiva-version-config.cmake"
                VERSION 1.0
                COMPATIBILITY AnyNewerVersion
        )

        install(TARGETS
                shiva
                EXPORT shiva-targets
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                )

        install(DIRECTORY
                ${CMAKE_CURRENT_SOURCE_DIR}/modules
                DESTINATION
                ${CMAKE_INSTALL_INCLUDEDIR}/shiva
                FILES_MATCHING PATTERN "*.h*" PATTERN "*.lua" PATTERN "*.cpp"
                )

        install(DIRECTORY
                ${CMAKE_CURRENT_SOURCE_DIR}/tools
                DESTINATION
                ${CMAKE_INSTALL_DATADIR}/shiva)

        install(EXPORT shiva-targets
                FILE shiva-targets.cmake
                NAMESPACE shiva::
                DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shiva
                )

        configure_package_config_file(
                "${PROJECT_SOURCE_DIR}/cmake/shiva-config.cmake.in"
                "${PROJECT_BINARY_DIR}/shiva-config.cmake"
                INSTALL_DESTINATION lib/cmake/shiva
        )

        install(FILES
                "${PROJECT_BINARY_DIR}/shiva-config.cmake"
                "${PROJECT_BINARY_DIR}/shiva-version-config.cmake"
                "${PROJECT_SOURCE_DIR}/cmake/x64-windows-shiva.cmake"
                DESTINATION lib/cmake/shiva)
    endif ()
endif ()
