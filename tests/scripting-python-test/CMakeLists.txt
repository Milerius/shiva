set(SOURCES script-python-test.cpp)
CREATE_UNIT_TEST(script-python-test shiva: "${SOURCES}")
target_link_libraries(script-python-test shiva::world shiva::pyscripting shiva::examples)
magic_source_group(script-python-test)
