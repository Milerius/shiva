set(CMAKE_POSITION_INDEPENDENT_CODE ON)
macro(generate_local_plugin SOURCES EXECUTABLE)
    add_library(${EXECUTABLE} SHARED "${SOURCES}")
    target_link_libraries(${EXECUTABLE} shiva::world)
    set_property(TARGET ${EXECUTABLE} PROPERTY POSITION_INDEPENDENT_CODE ON)
    set_target_properties(${EXECUTABLE}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/systems_test"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/systems_test"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/systems_test"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/systems_test"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/systems_test"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/systems_test"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/systems_test")
endmacro()

set(SOURCES ecs-test.cpp)
CREATE_UNIT_TEST(ecs-test shiva: "${SOURCES}")

generate_local_plugin("plugins/system_plugged_bar.hpp;plugins/system_plugged_bar.cpp" shiva-system-plugin-bar)

if(EMSCRIPTEN)
    #target_compile_options(system-plugin-bar PUBLIC -s SIDE_MODULE=1)
    set_target_properties(system-plugin-bar PROPERTIES
            COMPILE_OPTIONS "-s WASM=0 -s SIDE_MODULE=1 -s BUILD_AS_SHARED_LIB=1 -s EXPORT_ALL=1 -s DISABLE_EXCEPTION_CATCHING=0 -s FORCE_FILESYSTEM=1 -s SINGLE_FILE=1 -s BINARYEN_ASYNC_COMPILATION=0"
            LINK_FLAGS "-s WASM=0 -s SIDE_MODULE=1 -s BUILD_AS_SHARED_LIB=1 -s EXPORT_ALL=1 -s DISABLE_EXCEPTION_CATCHING=0 -s FORCE_FILESYSTEM=1 -s SINGLE_FILE=1 -s BINARYEN_ASYNC_COMPILATION=0")
    set_target_properties(ecs-test PROPERTIES
            COMPILE_OPTIONS "-s MAIN_MODULE=1 -s WASM=0 -s DEMANGLE_SUPPORT=1 -s EXPORT_ALL=1 -s DISABLE_EXCEPTION_CATCHING=0 -s FORCE_FILESYSTEM=1 -s SINGLE_FILE=1 -s BINARYEN_ASYNC_COMPILATION=0 --embed-file ${CMAKE_SOURCE_DIR}/bin/systems_test@/systems_test"
            LINK_FLAGS "-s MAIN_MODULE=1 -s WASM=0 -s DEMANGLE_SUPPORT=1 -s EXPORT_ALL=1 -s DISABLE_EXCEPTION_CATCHING=0 -s FORCE_FILESYSTEM=1 -s SINGLE_FILE=1 -s BINARYEN_ASYNC_COMPILATION=0 --embed-file ${CMAKE_SOURCE_DIR}/bin/systems_test@/systems_test"
            SUFFIX ".js")
endif()

target_link_libraries(ecs-test shiva::world)
target_compile_options(ecs-test PUBLIC $<$<PLATFORM_ID:Linux>:-Wno-unused-variable>)
add_dependencies(ecs-test shiva-system-plugin-bar)

magic_source_group(ecs-test)
