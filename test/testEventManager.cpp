/*
** test.cpp for EventManager in /home/wyzlic_a/delivery/EventManager/test.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Apr 21 04:45:02 2017 Dimitri Wyzlic
** Last update Fri Apr 21 04:45:02 2017 Dimitri Wyzlic
*/

/*
** evManager.cpp for plazza in /home/wyzlic_a/delivery/plazza/evManager.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Apr 19 15:49:58 2017 Dimitri Wyzlic
** Last update Wed Apr 19 15:49:58 2017 Dimitri Wyzlic
*/

#include "AlfredBase/EventManager/EventManager.hpp"

class A
{
public:
    void hello(std::string &src)
    {
        (void) src;
        // src is optional
        std::cout << "Hello" << std::endl;
    }

    A()
    {
        Alfred::EventManager::Manager::control()->createEvent("one");
        Alfred::EventManager::Manager::control()->watch("one", this, &A::hello);
    }
};

class B
{
public:
    void launch()
    {
        Alfred::EventManager::Manager::control()->fire("one");
    }
};

int main()
{
    auto a = new A;
    auto b = new B;

    b->launch();
    Alfred::EventManager::Manager::control()->dump();
    Alfred::EventManager::Manager::control()->clear();
    Alfred::EventManager::Manager::control()->dump();
    return (0);
}