set(SOURCES script-lua-test.cpp)
CREATE_UNIT_TEST(script-lua-test shiva: "${SOURCES}")
target_link_libraries(script-lua-test shiva::world shiva::lua shiva::examples)

add_custom_command(TARGET script-lua-test PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tests/scripting-lua-test/scripts ${CMAKE_SOURCE_DIR}/bin/assets/scripts)

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(script-lua-test PROPERTIES LINK_FLAGS "-s EXPORT_ALL=1 -s DISABLE_EXCEPTION_CATCHING=0 -s FORCE_FILESYSTEM=1 -s SINGLE_FILE=1 -s BINARYEN_ASYNC_COMPILATION=0 --preload-file ${CMAKE_SOURCE_DIR}/bin/assets@/assets")
endif ()
magic_source_group(script-lua-test)
