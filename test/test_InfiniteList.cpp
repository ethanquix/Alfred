/*
** test_InfiniteList.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/test_InfiniteList.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu Aug 31 20:23:44 2017 Dimitri Wyzlic
** Last update Thu Aug 31 20:23:44 2017 Dimitri Wyzlic
*/

#include "InfiniteList.hpp"

int next(Alfred::InfiniteList<int> &cur)
{
    return cur.getIdx();
}

bool isPrime(int x)
{
    for (size_t i = 2; i <= x / 2; ++i) {
        if (x % i == 0)
            return false;
    }
    return true;
}

std::string test(int x)
{
    return std::to_string(x) + "bonjour";
}

int main()
{
    Alfred::InfiniteList<int> l(0);
    l.setNextFunc(next);

//    l[100];

//    std::function<std::string(int)> a;
//    a = test;

//    l.map_to(a, 10).print();

//    std::cout << l << std::endl;

    std::cout << l.filter(isPrime).enumerate([](int x) -> bool { return x > 1500; }) << std::endl;
}
