set(SOURCES ecs-test.cpp)
CREATE_UNIT_TEST(ecs-test RS: "${SOURCES}")

add_source_group_now()

target_link_libraries(ecs-test shiva::world)