/*
** testRandom.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testRandom.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Mon Sep 18 01:18:43 2017 Dimitri Wyzlic
** Last update Mon Sep 18 01:18:43 2017 Dimitri Wyzlic
*/

#include <iostream>
#include "AlfredBase/Random/Random.hpp"

int main()
{
    std::cout << Alfred::Random::string(40) << std::endl;
    std::cout << Alfred::Random::string(40) << std::endl;
    std::cout << Alfred::Random::string(40) << std::endl;
}