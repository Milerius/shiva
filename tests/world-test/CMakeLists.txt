set(SOURCES world-test.cpp)
CREATE_UNIT_TEST(world-test RS: "${SOURCES}")
target_compile_features(world-test cxx_alias_templates)