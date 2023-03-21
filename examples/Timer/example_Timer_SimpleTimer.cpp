#include <iostream>
#include "Alfred/Timer/Perf"

int main()
{
    Alfred::Time::PerfTimer t;

    std::cout << t.capture()->get() << std::endl;

    int i = 0;
    t.reset();

    while (i < 1000)
        i++;

    std::cout << t.capture()->getMilli() << std::endl;

}