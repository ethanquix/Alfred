/*
** testTimer.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testTimer.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu Jun 01 01:09:51 2017 Dimitri Wyzlic
** Last update Thu Jun 01 01:09:51 2017 Dimitri Wyzlic
*/

#include <gtest/gtest.h>
#include <iostream>
#include "AlfredBase/Timer/Timer.hpp"

void funcUpdate(const std::string &str)
{
    std::cout << str << std::endl;
}

void funcUpdateAsync(const std::string &str)
{
    std::cout << "Async: " << str << std::endl;
}

void testAsync()
{
    Alfred::Time::Timer *a = new Alfred::Time::Timer(3, funcUpdateAsync);
    a->asyncStart();
}

TEST(Timer, checkpoint)
{
    int i = 0;

//    testAsync();
    Alfred::Time::Timer t(2, funcUpdate);
    t.addCheckpoint(1, "salut", [&]() {
        i += 1;;
    });

    t.start();

    while (t.update()); //or t.run();

    ASSERT_EQ(i, 1);
}

TEST(Timer, CheckpointAlreadyExist)
{
    Alfred::Time::Timer t(3, funcUpdate);
    t.addCheckpoint(2, "salut", []() {});

    ASSERT_THROW(t.addCheckpoint(2, "salut", []() {}),
                 Alfred::Time::TimerCheckpointAlreadyExist);

    t.start();
}