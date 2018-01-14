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
#include "AlfredBase/EventManager/EventManager.hpp"

static std::string verif = "";

void display(std::string x)
{
    verif += x;
}

TEST(EventManager, Return)
{
    Alfred::EventManager::Manager m;
    int ret = 0;

    m.addEvent<void, std::string>("test event return");

    m.listen<int, int>("test event return", [&] (int x) -> int {
        ret += x;
        return 1;
    });

    m.listen<int, int>("test event return", [&] (int x) -> int {
        ret += x;
        return 2;
    });

    auto retOfCallback = m.fire<int, int>("test event return", 1);

    ASSERT_EQ(ret, 2);

    for (const auto &it: retOfCallback)
        ret += it;

    ASSERT_EQ(ret, 5);
}

TEST(EventManager, Call)
{
    Alfred::EventManager::Manager m;

    m.addEvent<int, int>("test event call");

    std::function<void(std::string)> function = display;

    m.listen<void, std::string>("test event call", display);
    m.listen<void, std::string>("test event call", function);
    m.listen<void, std::string>("test event call", [] (std::string x) -> void { display(x); });

    std::string a = "a";

    m.fire<void, std::string>("test event call", a);

    ASSERT_EQ(verif, "aaa");
}

TEST(EventManager, unlisten)
{
    int i = 0;
    Alfred::EventManager::EventListener listener;

    Alfred::EventManager::Manager m;

    m.addEvent<void, int *>("test unlisten");

    m.listen<void, int *>("test unlisten", [] (int *ii) -> void {
        *ii += 1;
    });

    listener = m.listen<void, int *>("test unlisten", [] (int *ii) -> void {
        *ii += 1;
    });

    m.unlisten<void, int *>("test unlisten", listener);

    m.fire<void, int *>("test unlisten", &i);
    ASSERT_EQ(i, 1);
}