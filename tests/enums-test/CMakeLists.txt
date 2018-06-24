set(SOURCES enums-test.cpp)
CREATE_UNIT_TEST(enums-test shiva: "${SOURCES}")
target_link_libraries(enums-test shiva::enums)
magic_source_group(enums-test)