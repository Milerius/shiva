//
// Created by roman Sztergbaum on 27/06/2018.
//

#include <gtest/gtest.h>
#include <systems/all_systems.hpp>
#include <shiva/world/world.hpp>
#include <shiva/python/python_system.hpp>
#include <shiva/ecs/components/all.hpp>

class fixture_scripting : public ::shiva::world, public ::testing::Test
{
public:
    using systems_list = shiva::meta::type_list<shiva::scripting::python_system,
        shiva::examples::post_system,
        shiva::examples::pre_system>;
protected:
    void SetUp() override
    {
        system_ptr = std::addressof(system_manager_.create_system<shiva::scripting::python_system>());
        system_ptr->register_entity_registry();
        system_ptr->register_components(shiva::ecs::common_components{});
        //system_ptr->register_types_list(fixture_scripting::systems_list{});
        //system_ptr->register_world();
        ASSERT_TRUE(system_ptr->load_script("basic_tests.py"));
        system_ptr->update();
        dispatcher_.trigger<shiva::event::start_game>();
    }

    void TearDown() override
    {
        spdlog::drop_all();
    }

protected:
    shiva::scripting::python_system *system_ptr{nullptr};
};

TEST(scripting_python, basic)
{
    ASSERT_EQ(1, 1);
}

TEST_F(fixture_scripting, create_entity)
{
    pybind11::module &module = this->system_ptr->get_module();
    py::object obj = module.attr("basic_tests").attr("test_create_entity");
    auto result = obj().cast<bool>();
    ASSERT_TRUE(result);
}

TEST_F(fixture_scripting, destroy_entity)
{
    pybind11::module &module = this->system_ptr->get_module();
    py::object obj = module.attr("basic_tests").attr("test_destroy_entity");
    auto result = obj().cast<bool>();
    ASSERT_TRUE(result);
}

TEST_F(fixture_scripting, components)
{
    pybind11::module &module = this->system_ptr->get_module();
    py::object obj = module.attr("basic_tests").attr("test_component");
    auto result = obj().cast<bool>();
    ASSERT_TRUE(result);
}

TEST_F(fixture_scripting, for_each)
{
    pybind11::module &module = this->system_ptr->get_module();
    py::object obj = module.attr("basic_tests").attr("test_for_each");
    auto result = obj().cast<bool>();
    ASSERT_TRUE(result);
}

TEST_F(fixture_scripting, for_each_runtime)
{
    pybind11::module &module = this->system_ptr->get_module();
    py::object obj = module.attr("basic_tests").attr("test_for_each_runtime");
    auto result = obj().cast<bool>();
    ASSERT_TRUE(result);
}

TEST_F(fixture_scripting, systems)
{
    ASSERT_TRUE(system_ptr->load_all_scripted_systems());
    ASSERT_GE(system_manager_.update(), 2u);
}