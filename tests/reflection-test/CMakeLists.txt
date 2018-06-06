set(SOURCES reflection-test.cpp)
CREATE_UNIT_TEST(reflection-test Shiva: "${SOURCES}")
target_link_libraries(reflection-test shiva::reflection)
