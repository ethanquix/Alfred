/*
** testNetwork.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testNetwork.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Jul 12 01:56:18 2017 Dimitri Wyzlic
** Last update Wed Jul 12 01:56:18 2017 Dimitri Wyzlic
*/

#include <vector>
#include "INetwork.hpp"
#include "ISerializer.hpp"
#include "../src/Network/Serializer/BasicSerializer.hpp"

struct Test
{
    int a;
    int b;
    std::vector<std::string> *c;
};

int main()
{
    auto tmp = new char[sizeof(Test)];
    Alfred::BasicSerializer<Test *, char *> s;
    auto *test = new Test();
    auto *final = new Test();

    test->a = 40;
    test->b = 60;
    test->c = new std::vector<std::string>;
    test->c->push_back("yop");
    test->c->push_back("ca");
    test->c->push_back("marche");


    //Magic here
    tmp = s.serialize(test, tmp);
    final = s.deserialize(final, tmp);

    std::cout << final->a << std::endl;

    for (const auto &it : *(final->c))
        std::cout << it << std::endl;
}