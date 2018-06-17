//
// Created by doom on 02/02/18
//

#include <functional>
#include <gtest/gtest.h>
#include <shiva/meta/visitor.hpp>
#include <shiva/reflection/reflection.hpp>

namespace
{
    class i_dont_like_refl
    {
    };

    class i_like_refl
    {
    public:
        i_like_refl(int i, const std::string &s, double d) noexcept : _i(i), _s(s), _d(d)
        {
        }

    private:
        int _i;
        std::string _s;
        double _d;

    public:
        static constexpr auto reflectedMembers() noexcept
        {
            return shiva::meta::makeMap(
                reflect_member(&i_like_refl::_i),
                reflect_member(&i_like_refl::_s),
                reflect_member(&i_like_refl::_d)
            );
        }
    };

    struct i_have_a_reflectible_name
    {
        reflect_class(i_have_a_reflectible_name);
    };

    struct i_have_refl_member_functions
    {
        int func(int i)
        {
            return i;
        }

        static constexpr auto reflectedFunctions() noexcept
        {
            return shiva::meta::makeMap(reflect_function(&i_have_refl_member_functions::func));
        }
    };
}

TEST(reflection, traits)
{
    ASSERT_TRUE(shiva::refl::has_reflectible_members_v<i_like_refl>);
    ASSERT_FALSE(shiva::refl::has_reflectible_functions_v<i_like_refl>);

    ASSERT_TRUE(shiva::refl::has_reflectible_functions_v<i_have_refl_member_functions>);
    ASSERT_FALSE(shiva::refl::has_reflectible_members_v<i_have_refl_member_functions>);

    ASSERT_TRUE(shiva::refl::is_reflectible_v<i_like_refl>);
    ASSERT_TRUE(shiva::refl::is_reflectible_v<i_have_refl_member_functions>);
    ASSERT_FALSE(shiva::refl::is_reflectible_v<i_dont_like_refl>);

    ASSERT_TRUE(shiva::refl::has_reflectible_class_name_v<i_have_a_reflectible_name>);
    ASSERT_FALSE(shiva::refl::has_reflectible_class_name_v<i_like_refl>);
    ASSERT_FALSE(shiva::refl::has_reflectible_class_name_v<i_have_refl_member_functions>);
}

TEST(reflection, members)
{
    using namespace std::literals;

    //Dummy values to ensure initialization
    int i = -1;
    std::string s;
    double d = -1.;

    i_like_refl ilr{1, "salut", 3.2};

    auto visitor = shiva::meta::makeVisitor([&i, &ilr](auto &&, int i_like_refl::* iPtr) {
        i = ilr.*iPtr;
    }, [&s, &ilr](auto &&, std::string i_like_refl::* sPtr) {
        s = ilr.*sPtr;
    }, [&d, &ilr](auto &&, double i_like_refl::* dPtr) {
        d = ilr.*dPtr;
    });

    shiva::meta::for_each(i_like_refl::reflectedMembers(), visitor);
    ASSERT_EQ(i, 1);
    ASSERT_EQ(s, "salut");
    ASSERT_EQ(d, 3.2);

    i = -1;
    s.clear();

    shiva::refl::getMember(i_like_refl::reflectedMembers(), "_i"sv, visitor);
    shiva::refl::getMember(i_like_refl::reflectedMembers(), "_s"sv, visitor);
    auto dPtrOpt = shiva::refl::getMember<double i_like_refl::*>(i_like_refl::reflectedMembers(), "_d"sv);
    auto emptyOpt = shiva::refl::getMember<char i_like_refl::*>(i_like_refl::reflectedMembers(), "_c"sv);
    auto non_existent = shiva::refl::getMember<long i_like_refl::*>(i_like_refl::reflectedMembers(), "_s"sv);

    ASSERT_FALSE(non_existent);
    ASSERT_EQ(i, 1);
    ASSERT_EQ(s, "salut");
    ASSERT_TRUE(dPtrOpt);
    auto dPtr = *dPtrOpt;
    ASSERT_EQ(ilr.*dPtr, 3.2);
    ASSERT_FALSE(emptyOpt);
}

TEST(reflection, member_functions)
{
    using namespace std::literals;

    int i = 0;

    shiva::refl::getFunction(i_have_refl_member_functions::reflectedFunctions(), "func"sv, ([&i](auto &&, auto &&v) {
        i_have_refl_member_functions iharmf;
        i = std::invoke(v, iharmf, 1);
    }));
    ASSERT_EQ(i, 1);

    i_have_refl_member_functions iharf2;
    i = shiva::refl::callFunction<int(int)>(i_have_refl_member_functions::reflectedFunctions(), "func", &iharf2, 2);
    ASSERT_EQ(i, 2);

    i = shiva::refl::callFunction<int(int)>(i_have_refl_member_functions::reflectedFunctions(), "func", iharf2, 3);
    ASSERT_EQ(i, 3);

    ASSERT_THROW(shiva::refl::callFunction<int()>(i_have_refl_member_functions::reflectedFunctions(), "lala", iharf2),
                 shiva::refl::MemberNotFound);
    shiva::refl::MemberNotFound mnf;

    ASSERT_EQ(std::string(mnf.what()), "Member not found");
}

TEST(reflection, class_name)
{
    ASSERT_EQ(i_have_a_reflectible_name::class_name(), "i_have_a_reflectible_name");
}
