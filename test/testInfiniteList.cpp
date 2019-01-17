/*
** test_InfiniteList.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/test_InfiniteList.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu Aug 31 20:23:44 2017 Dimitri Wyzlic
** Last update Thu Aug 31 20:23:44 2017 Dimitri Wyzlic
*/

#include <gtest/gtest.h>

#include "Alfred/Infinite/InfiniteList.hpp"
#include "Alfred/Infinite/premade/InfiniteListPremade.hpp"

void calc_primeNumber_to(int max);
void calc_square_primeNumber_num(int max);
void calc_fibo(int max);

bool isPrime(int x)
{
    for (size_t i = 2; i <= x / 2; ++i) {
        if (x % i == 0)
            return false;
    }
    return true;
}

TEST(InfiniteList, Counter)
{
    Alfred::Infinite::InfiniteList<int> l(0);
    l.setNextFunc(Alfred::Infinite::Premade::premade_Counter);

    auto list  = l
        .map_to([] (int x) -> std::string { return std::to_string(x); }, 10)
        .map([](std::string x) -> std::string { return x + " ieme nb"; })
        .end();

    auto out = list.extract();
    auto verif = std::vector<std::string>({"0 ieme nb", "1 ieme nb", "2 ieme nb", "3 ieme nb", "4 ieme nb", "5 ieme nb", "6 ieme nb", "7 ieme nb", "8 ieme nb", "9 ieme nb"});

    ASSERT_EQ(verif, out);
}

TEST(InfiniteList, PrimeNumber)
{
    Alfred::Infinite::InfiniteList<int> l(0);
    l.setNextFunc(Alfred::Infinite::Premade::premade_Counter);

    l
        .filter(isPrime)
        .enumerate([](int x) -> bool { return x > 100; });

    auto out = l.extract();
    auto verif = std::vector<int>({ 0, 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 });

    ASSERT_EQ(verif, out);
}

TEST(InfiniteList, SquarePrimeNumber)
{
    Alfred::Infinite::InfiniteList<int> l(0);
    l.setNextFunc(Alfred::Infinite::Premade::premade_Counter);

    l
        .filter(isPrime)
        .map([](int x) -> int { return x * x; })
        .limit(10);

    auto out = l.extract();
    auto verif = std::vector<int>({0, 1, 4, 9, 25, 49});

    ASSERT_EQ(verif, out);
}

TEST(InfiniteList, Fibonnacci)
{
    Alfred::Infinite::InfiniteList<int> l(0);
    l.setNext(1);

    l.setNextFunc(Alfred::Infinite::Premade::premade_Fibonnacci);
    l.get(6);

    auto out = l.extract();
    auto verif = std::vector<int>({0, 1, 1, 2, 3, 5, 8});

    ASSERT_EQ(verif, out);
}