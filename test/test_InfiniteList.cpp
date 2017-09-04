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

void calc_primeNumber_to(int max);
void calc_square_primeNumber_num(int max);
void calc_fibo(int max);

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

    std::function<std::string(int)> to_str_func = test;

    std::cout << l.map_to(to_str_func, 10).map([](std::string x) -> std::string { return x + "_aurevoir"; }).end();
    //Above line will throw if .limit(>10) because it will need to access next function but not defined
    calc_primeNumber_to(11);
    calc_square_primeNumber_num(11);
    calc_fibo(10);
}

void calc_primeNumber_to(int max)
{
    Alfred::InfiniteList<int> l(0);
    l.setNextFunc(Alfred::module_Counter);
    std::cout << l.filter(isPrime).enumerate([max](int x) -> bool { return x > max; }) << std::endl;
}

void calc_square_primeNumber_num(int max)
{
    Alfred::InfiniteList<int> l(0);
    l.setNextFunc(Alfred::module_Counter);
    std::cout << l.filter(isPrime).map([](int x) -> int { return x * x; }).limit(max) << std::endl;
}

void calc_fibo(int max)
{
    Alfred::InfiniteList<int> l(0);
    l.setNext(1);

    l.setNextFunc(Alfred::module_Fibonnacci);
    l.get(max);
    std::cout << l << std::endl;
}