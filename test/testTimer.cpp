/*
** testTimer.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testTimer.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu Jun 01 01:09:51 2017 Dimitri Wyzlic
** Last update Thu Jun 01 01:09:51 2017 Dimitri Wyzlic
*/

#include <iostream>
#include "AlfredBase/Timer/Timer.hpp"

void funcUpdate(const std::string &str) {
    std::cout << str << std::endl;
}

void funcUpdateAsync(const std::string &str) {
    std::cout << "Async: " << str << std::endl;
}

void testAsync()
{
    Alfred::Time::Timer *a = new Alfred::Time::Timer(3, funcUpdateAsync);
    a->asyncStart();
}

int main()
{
    testAsync();
    Alfred::Time::Timer t(3, funcUpdate);
    t.addCheckpoint(2, "salut", [] () {std::cout << "Yop" << std::endl;});
    t.deleteCheckpoint("salut");
    t.start();
    while (t.update()); //or t.run();
    return (0);
}