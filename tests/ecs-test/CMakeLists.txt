set(SOURCES ecs-test.cpp)
CREATE_UNIT_TEST(ecs-test RS: "${SOURCES}")
target_link_libraries(ecs-test shiva::world)