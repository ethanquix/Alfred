#include <AlfredBase/Utils/Defer.hpp>
#include <AlfredBase/Utils/Counter.hpp>
#include <iostream>

int main()
{
    Alfred::Utils::Defer d([] () { std::cout << "I am at the function return"  << std::endl;});

    DEFER([] () { std::cout << "I am a unique defer !" << std::endl;} );
    DEFER([] () { std::cout << "I am another unique defer !" << std::endl;} );

    std::cout << "I am before defer" << std::endl;

    std::cout << Alfred::Utils::Counter<int>() << std::endl;
    std::cout << Alfred::Utils::Counter<int>() << std::endl;
    std::cout << Alfred::Utils::Counter<int>() << std::endl;
    std::cout << Alfred::Utils::Counter<int>() << std::endl;

    std::cout << Alfred::Utils::Counter<float>() << std::endl;
    std::cout << Alfred::Utils::Counter<float>() << std::endl;
    std::cout << Alfred::Utils::Counter<float>() << std::endl;
    std::cout << Alfred::Utils::Counter<float>() << std::endl;
}