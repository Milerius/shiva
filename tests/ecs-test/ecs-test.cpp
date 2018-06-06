//
// Created by roman Sztergbaum on 30/05/2018.
//

#include <gtest/gtest.h>
//#include <shiva/ecs/eastl_static.hpp>
//#include <EASTL/allocator_malloc.h>
//#include <EASTL/vector.h>
#include <shiva/reflection/reflection.hpp>
#include <shiva/ecs/ecs.hpp>
#include <entt/signal/dispatcher.hpp>
#include <shiva/ecs/system_manager.hpp>

TEST(ecs_testing, constructor)
{
  //  eastl::vector<int, eastl::allocator_malloc> vec;

 //   vec.push_back(1);
 //   ASSERT_EQ(vec.size(), 1);
    entt::Dispatcher dispatcher{};
    entt::DefaultRegistry registry{};
    shiva::ecs::system_manager manager(dispatcher, registry);
    ASSERT_EQ(1, 1);
}

