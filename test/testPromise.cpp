#include "../src/Promise/Promise.hpp"
#include <iostream>
#include <unistd.h>

int test(int i)
{
    usleep(5000);
    std::cout << i << std::endl;
    return i + 1;
}

int main()
{
    int a = 3;
    int b = 4;

    std::function<int(int)> f = test;

    Alfred::Promise<int, int> p([&p](int) -> int { p.resolve(4); });
    std::cout << "Hey" << std::endl;

    p.then(test).then(test).then(test).then(test).then(test).then(test).then(test);

    std::cout << "It's async !" << std::endl;
    usleep(50000);
}
