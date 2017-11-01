/*
** Random.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/Random.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Mon Sep 18 01:18:28 2017 Dimitri Wyzlic
** Last update Mon Sep 18 01:18:28 2017 Dimitri Wyzlic
*/

#pragma once

#include <algorithm>
#include <random>
#include <config.hpp>

namespace Alfred
{
    namespace Random
    {
        static const std::string &string(const size_t max)
        {
            auto randchar = []() -> char {
                const size_t max_index = (sizeof(RANDOM_STRING_CHARS) - 1);
                return RANDOM_STRING_CHARS[rand() % max_index];
            };
            auto str = new std::string(max, 0);
            std::generate_n(str->begin(), max, randchar);
            return *str;
        }

        static const int randint(size_t min, size_t max)
        {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> uni(min, max);
            return (uni(rng));
        }
    }
}