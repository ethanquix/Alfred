#include <iostream>
#include "AlfredBase/Timer/SimpleTimer.hpp"

int main()
{
    Alfred::Time::SimpleTimer t;

    std::cout << t.elapsed() << std::endl;

    int i = 0;
    t.restart();

    while (i < 1000)
        i++;

    std::cout << t.elapsed() << std::endl;

}