set(SOURCES script-python-test.cpp)
CREATE_UNIT_TEST(script-python-test shiva: "${SOURCES}")

add_custom_command(TARGET script-python-test PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tests/scripting-python-test/scripts ${CMAKE_SOURCE_DIR}/bin/assets/scripts)

if (EMSCRIPTEN)
    #set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(script-lua-test PROPERTIES LINK_FLAGS "-s EXPORT_ALL=1 -s DISABLE_EXCEPTION_CATCHING=0 -s FORCE_FILESYSTEM=1 -s SINGLE_FILE=1 -s BINARYEN_ASYNC_COMPILATION=0 --embed-file /Users/romansztergbaum/Documents/shiva/bin/assets")
endif ()

target_link_libraries(script-python-test shiva::world shiva::pyscripting shiva::examples)
magic_source_group(script-python-test)
