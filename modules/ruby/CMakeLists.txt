include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(shiva::ruby "${MODULE_SOURCES}" ${MODULE_PATH})

find_package(Ruby 2.5 REQUIRED)

if (Ruby_FOUND)
    message(STATUS "Ruby version is ${RUBY_VERSION}")
    message(STATUS "Ruby library path is ${RUBY_LIBRARY}")
    if (RUBY_INCLUDE_DIRS)
        target_include_directories(ruby INTERFACE ${RUBY_INCLUDE_DIRS})
        message(STATUS "Ruby include directory is ${RUBY_INCLUDE_DIRS}")
    else ()
        # CMake 2.6 compatibility -- FindRuby used to set RUBY_INCLUDE_PATH
        target_include_directories(ruby INTERFACE ${RUBY_INCLUDE_PATH})
        message(STATUS "Ruby include directory is ${RUBY_INCLUDE_PATH}")
    endif ()
else ()
    message(ERROR "Ruby not found")
endif ()

if (UNIX)
    target_compile_options(ruby INTERFACE $<$<CONFIG:DEBUG>:
            -Wno-register
            -Wno-old-style-cast
            -Wno-disabled-macro-expansion
            -Wno-used-but-marked-unused>)
    target_compile_options(ruby INTERFACE $<$<CONFIG:RELEASE>:
            -Wno-register
            -Wno-old-style-cast
            -Wno-disabled-macro-expansion
            -Wno-used-but-marked-unused>)
endif ()

target_link_libraries(ruby INTERFACE shiva::ecs ${RUBY_LIBRARY})

AUTO_TARGETS_MODULE_INSTALL(ruby)