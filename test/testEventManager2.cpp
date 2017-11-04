//      ___  _  __              _   _____
//    / _ \| |/ _|            | | |  ___|
//   / /_\ \ | |_ _ __ ___  __| | | |__  ___ ___ 
//  |  _  | |  _| '__/ _ \/ _` | |  __|/ __/ __|
//  | | | | | | | | |  __/ (_| | | |__| (__\__ \
//  \_| |_/_|_| |_|  \___|\__,_| \____/\___|___/

// testEventManager2.cpp created 03/11/17

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