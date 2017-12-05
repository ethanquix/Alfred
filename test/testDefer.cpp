#include <AlfredBase/Utils/Defer.hpp>
#include <AlfredBase/Utils/Counter.hpp>
#include <iostream>
#include <AlfredBase/Utils/MapSingleton.hpp>
#include <gtest/gtest.h>


class Foo : public Alfred::Utils::MapSingleton<int, Foo>
{
  public:
    int _value = 0;
};

TEST(DeferTest, Positive)
{
    int *x = new int();
    *x = 0;

    Alfred::Utils::Defer d([&] () { *x += 1; });

    DEFER([&] () { *x += 1;} );
    DEFER([&] () { *x += 1;} );

    ASSERT_EQ(*x, 0);
}

TEST(CounterTest, Positive)
{
    ASSERT_EQ(Alfred::Utils::Counter<int>(), 0);
    ASSERT_EQ(Alfred::Utils::Counter<int>(), 1);

    ASSERT_EQ(Alfred::Utils::Counter<float>(), 0);
    ASSERT_EQ(Alfred::Utils::Counter<float>(), 1);
}

TEST(SingletonTest, Positive)
{
    Foo::getSingleton(1)._value = 3;
    Foo::getSingleton(2)._value = 4;

    ASSERT_EQ(Foo::getSingleton(1)._value, 3);
    ASSERT_EQ(Foo::getSingleton(2)._value, 4);
}