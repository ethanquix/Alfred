#include "AlfredBase/Async/Promise.hpp"
#include <iostream>
#include <unistd.h>

int test(int i)
{
    usleep(500000);
    std::cout << i << std::endl;
    return i + 1;
}

int main()
{
    std::function<int(int)> f = test;

    Alfred::Async::Promise<int, int> p([&p](int) -> int { p.resolve(4); });
    std::cout << "Hey" << std::endl;

    p.then(test).then(test).then(test).then(test).then(test).then(test).then(test);

    std::cout << "It's async !" << std::endl;
    usleep(5000000);
}
