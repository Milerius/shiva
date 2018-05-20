set(SOURCES world-test.cpp)
CREATE_UNIT_TEST(world-test RS: "${SOURCES}")
target_add_build_information(world-test)
#target_link_libraries()