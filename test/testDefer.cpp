#include <Defer.hpp>
#include <iostream>

int main()
{
    Alfred::Utils::Defer d([] () { std::cout << "I am at the function return"  << std::endl;});

    DEFER([] () { std::cout << "I am a unique defer !" << std::endl;} );
    DEFER([] () { std::cout << "I am a unique defer !" << std::endl;} );
    DEFER([] () { std::cout << "I am a unique defer !" << std::endl;} );
    DEFER([] () { std::cout << "I am a unique defer !" << std::endl;} );
    DEFER([] () { std::cout << "I am a unique defer !" << std::endl;} );
    DEFER([] () { std::cout << "I am a unique defer !" << std::endl;} );

    std::cout << "I am before defer" << std::endl;
}