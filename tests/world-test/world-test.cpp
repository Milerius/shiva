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
        spdlog::drop_all();
    }
};

TEST_F(fixture_world, run)
{
    ASSERT_EQ(this->run(), 0);
}

TEST_F(fixture_world, error_handler)
{

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
    ASSERT_DEATH(shiva::error::general_handler::handler(1), "");
#pragma clang diagnostic pop
}
