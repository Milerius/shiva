set(SOURCES script-lua-test.cpp)
CREATE_UNIT_TEST(script-lua-test shiva: "${SOURCES}")
target_link_libraries(script-lua-test shiva::world shiva::lua shiva::examples)
magic_source_group(script-lua-test)
