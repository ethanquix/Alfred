#include <AlfredBase/Utils/Defer.hpp>
#include <AlfredBase/Utils/Counter.hpp>
#include <iostream>
#include <AlfredBase/Utils/MapSingleton.hpp>

class A : public Alfred::Utils::MapSingleton<int, A>
{
  public:
    int _value = 0;
};

int main()
{
    //Defer
    Alfred::Utils::Defer d([] () { std::cout << "I am at the function return"  << std::endl;});

    DEFER([] () { std::cout << "I am a unique defer !" << std::endl;} );
    DEFER([] () { std::cout << "I am another unique defer !" << std::endl;} );

    std::cout << "I am before defer" << std::endl;

    //Counter
    std::cout << Alfred::Utils::Counter<int>() << std::endl;
    std::cout << Alfred::Utils::Counter<int>() << std::endl;
    std::cout << Alfred::Utils::Counter<int>() << std::endl;
    std::cout << Alfred::Utils::Counter<int>() << std::endl;

    std::cout << Alfred::Utils::Counter<float>() << std::endl;
    std::cout << Alfred::Utils::Counter<float>() << std::endl;
    std::cout << Alfred::Utils::Counter<float>() << std::endl;
    std::cout << Alfred::Utils::Counter<float>() << std::endl;

    //Map Singleton
    A::getSingleton(1)._value = 3;
    A::getSingleton(2)._value = 4;

    std::cout << "A: 1 " << A::getSingleton(1)._value << std::endl;
    std::cout << "A: 2 " << A::getSingleton(2)._value << std::endl;
}