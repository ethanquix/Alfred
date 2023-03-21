/*
** test.cpp for EventManager in /home/wyzlic_a/delivery/EventManager/test.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Apr 21 04:45:02 2017 Dimitri Wyzlic
** Last update Fri Apr 21 04:45:02 2017 Dimitri Wyzlic
*/

#include <gtest/gtest.h>
#include <iostream>
#include "Alfred/EventManager/Manager.hpp"

static std::string verif = "";

void display(std::string x)
{
    verif += x;
}

TEST(EventManager, Return)
{
    Alfred::EventManager::Manager m;
    int ret = 0;

    m.addEvent<void, std::string>("test event return"_hash);

    m.listen<int, int>("test event return"_hash, [&] (int x) -> int {
        ret += x;
        return 1;
    });

    m.listen<int, int>("test event return"_hash, [&] (int x) -> int {
        ret += x;
        return 2;
    });

    auto retOfCallback = m.fireAndReturn<int, int>("test event return"_hash, 1);

    ASSERT_EQ(ret, 2);

    for (const auto &it: retOfCallback)
        ret += it;

    ASSERT_EQ(ret, 5);
}

TEST(EventManager, Call)
{
    Alfred::EventManager::Manager m;

    m.addEvent<int, int>("test event call"_hash);

    std::function<void(std::string)> function = display;

    m.listen<void, std::string>("test event call"_hash, display);
    m.listen<void, std::string>("test event call"_hash, function);
    m.listen<void, std::string>("test event call"_hash, [] (std::string x) -> void { display(x); });

    std::string a = "a";

    m.fire<void, std::string>("test event call"_hash, a);

    ASSERT_EQ(verif, "aaa");
}

TEST(EventManager, unlisten)
{
    int i = 0;
    Alfred::EventManager::EventListener listener;

    Alfred::EventManager::Manager m;

    m.addEvent<void, int *>("test unlisten"_hash);

    m.listen<void, int *>("test unlisten"_hash, [] (int *ii) -> void {
        *ii += 1;
    });

    listener = m.listen<void, int *>("test unlisten"_hash, [] (int *ii) -> void {
        *ii += 1;
    });

    m.unlisten<void, int *>("test unlisten"_hash, listener);

    m.fire<void, int *>("test unlisten"_hash, &i);
    ASSERT_EQ(i, 1);
}