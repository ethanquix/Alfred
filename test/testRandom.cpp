/*
** testRandom.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testRandom.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Mon Sep 18 01:18:43 2017 Dimitri Wyzlic
** Last update Mon Sep 18 01:18:43 2017 Dimitri Wyzlic
*/

#include <gtest/gtest.h>
#include "AlfredBase/Random/Random.hpp"

TEST(Random, String)
{
    const std::string &a = Alfred::Random::string(20);
    const std::string &b = Alfred::Random::string(20);

    ASSERT_EQ(a.size(), 20);
    ASSERT_EQ(b.size(), 20);

    ASSERT_NE(a, b);
}