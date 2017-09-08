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
    auto a = Alfred::MakeFraction(5, 3.14);
    auto b = Alfred::MakeFraction(a, 4);
    std::cout << static_cast<float>(b) << std::endl; // -> 0.398089
}