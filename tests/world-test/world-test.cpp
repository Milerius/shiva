//
// Created by sztergba on 02/05/2018.
//

#include <gtest/gtest.h>
#include <systems/all_systems.hpp>
#include <shiva/world/world.hpp>

class fixture_world : public ::shiva::world, public ::testing::Test
{
protected:
    void SetUp() override
    {
        system_manager_.load_systems<shiva::examples::post_system, shiva::examples::pre_system>();
    }

    void TearDown() override
    {
    }
};

TEST_F(fixture_world, run)
{
    ASSERT_EQ(this->run(), 0);
}
