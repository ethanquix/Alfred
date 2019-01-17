#include <iostream>
#include "Alfred/Timer/Perf"

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