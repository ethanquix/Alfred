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

#include <iostream>
#include "AlfredBase/EventManager/EventManager.hpp"

void display(std::string x)
{
    std::cout << "Je dois ecrire un truc " << x << std::endl;
}

int main()
{
    Alfred::EventManager::Manager m;

    std::function<void(std::string)> function = display;

    m.addEvent<void, std::string>("two");
    m.addEvent<int, int>("test ret");

    m.listen<int, int>("test ret", [] (int x) -> int {
        std::cout << "RESULT: " << x << std::endl;
        return 1;
    });

    m.listen<int, int>("test ret", [] (int x) -> int {
        std::cout << "RESULT: " << x << std::endl;
        return 2;
    });

    m.listen<void, std::string>("two", display);
    m.listen<void, std::string>("two", function);
    m.listen<void, std::string>("two", [] (std::string x) -> void { display(x); });

    m.fire<void, std::string>("two", "ma string");
    auto ret = m.fire<int, int>("test ret", 1);
    for (const auto &it: ret)
        std::cout << it << std::endl;
}