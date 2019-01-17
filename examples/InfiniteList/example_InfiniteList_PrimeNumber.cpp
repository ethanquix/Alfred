#include "Alfred/Infinite/InfiniteList.hpp"
#include "Alfred/Infinite/premade/InfiniteListPremade.hpp"


bool isPrime(int x)
{
    for (size_t i = 2; i <= x / 2; ++i) {
        if (x % i == 0)
            return false;
    }
    return true;
}

//TEST(InfiniteList, SquarePrimeNumber)
//{
//    Alfred::Infinite::InfiniteList<int> l(0);
//    l.setNextFunc(Alfred::Infinite::Premade::premade_Counter);
//
//    l
//        .filter(isPrime)
//        .map([](int x) -> int { return x * x; })
//        .limit(10);
//
//    auto out = l.extract();
//    auto verif = std::vector<int>({0, 1, 4, 9, 25, 49});
//
//    ASSERT_EQ(verif, out);
//}

int main()
{
    LOG_SET_CONSOLE;

    Alfred::Infinite::InfiniteList<int> primes(0);
    primes.setNextFunc(Alfred::Infinite::Premade::premade_Counter);

    primes
        .filter(isPrime)
        .enumerate([](int x) -> bool { return x > 100; });

    std::vector<int> list_of_primes = primes.extract();
//     { 0, 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

    std::string out = "";
    for (const auto p : list_of_primes)
        out +=  std::to_string(p) + " ";
    LOG_INFO << out << LOG_ENDL;

    int next = primes.next();
    // 101;
    LOG_INFO << next << LOG_ENDL;
}