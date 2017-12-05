#include "AlfredBase/Async/Promise.hpp"
#include <iostream>

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

void crossSleep(int ms)
{
#ifdef LINUX
    usleep(ms * 1000);
#endif
#ifdef WINDOWS
    Sleep(ms);
#endif
}

int test(int i)
{
    crossSleep(1000);
    std::cout << i << std::endl;
    return i + 1;
}

int main()
{
    std::function<int(int)> f = test;

    Alfred::Async::Promise<int, int> p([&](int) -> int { p.resolve(4); });
    std::cout << "Hey" << std::endl;

    p.then(test).then(test).then(test).then(test).then(test).then(test).then(test);

    std::cout << "It's async !" << std::endl;
    crossSleep(5000);
}
