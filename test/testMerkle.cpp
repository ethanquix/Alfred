/*
** testMerkle.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testMerkle.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu Aug 24 15:49:29 2017 Dimitri Wyzlic
** Last update Thu Aug 24 15:49:29 2017 Dimitri Wyzlic
*/

#include "Merkle.hpp"

std::string hash(int a)
{
    return std::to_string(a);
}

int main()
{
    Alfred::Merkle<int> tree(hash);
}
