#pragma once

#include "Alfred/config.hpp"

#include <string>
#include <algorithm>
#include <random>

namespace Alfred
{
    namespace Random
    {
        static const std::string &string(const size_t max)
        {
            auto *ret = new std::string();

            std::mt19937_64 gen{std::random_device()()};
            std::uniform_int_distribution<size_t> dist{0, sizeof(RANDOM_STRING_CHARS) - 1};
            std::generate_n(std::back_inserter(*ret), max, [&] { return RANDOM_STRING_CHARS[dist(gen)]; });
            return *ret;
        }

        static const int randint(size_t min, size_t max)
        {
            std::random_device rd;
            std::mt19937 rng(rd());
#pragma warning(disable:4267)
            std::uniform_int_distribution<int> uni(min, max);
            return (uni(rng));
        }

        template <typename X, typename Y>
        static const X rand(Y min, Y max)
        {
            std::random_device rd;
            std::mt19937 rng(rd());
#pragma warning(disable:4267)
            std::uniform_int_distribution<X> uni(min, max);
            return (uni(rng));
        };

        template <typename X>
        static const X rand(X min, X max)
        {
            std::random_device rd;
            std::mt19937 rng(rd());
#pragma warning(disable:4267)
            std::uniform_int_distribution<X> uni(min, max);
            return (uni(rng));
        }

    }
}