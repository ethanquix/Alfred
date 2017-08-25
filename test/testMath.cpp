/*
** testMath.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testMath.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Aug 23 20:00:33 2017 Dimitri Wyzlic
** Last update Wed Aug 23 20:00:33 2017 Dimitri Wyzlic
*/

#include "Math.hpp"

int main()
{
    Alfred::Matrix<int, 1, 2> a;

    a.setLine(0, 1);
    a.setLine(1, 3);
    a.print().translate().print();
}