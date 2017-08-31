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
    return cur.last() + 1;
}

int main()
{
    Alfred::InfiniteList<int> l(0);
    l.setNextFunc(next);

    std::cout << l[10] << std::endl;
    std::cout << l++;
    std::cout << l++;
}