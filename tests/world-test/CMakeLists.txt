set(SOURCES world-test.cpp)
CREATE_UNIT_TEST(world-test shiva: "${SOURCES}")
target_link_libraries(world-test shiva::world shiva::examples)
magic_source_group(world-test)