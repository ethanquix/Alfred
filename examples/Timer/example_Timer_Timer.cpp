#include <iostream>
#include "AlfredBase/Timer/Timer.hpp"

int main()
{
    Alfred::Time::Timer t;

    t.setOnTickCallback([] (std::string time) {
        std::cout << time << " elapsed" << std::endl;
    });

    t.setEndCallback([] () { std::cout << "Timer done" << std::endl; });

    t.addCheckpoint(5, "checkpoint after 5sec", [] () {
        std::cout << "5sec have passed !" << std::endl;
    });

    t.setup(); // Set base time

    t.run(); // t.run(true) -> async
}