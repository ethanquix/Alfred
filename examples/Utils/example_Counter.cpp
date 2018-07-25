#include <AlfredBase/Utils/Counter.hpp>
#include <iostream>

typedef int Bar;

class Foo
{
    public:
    int id = Alfred::Utils::Counter<Foo>();

    Foo()
    {}
};

int main()
{
    auto a = Foo();
    auto b = Foo();
    auto c = Foo();

    std::cout << a.id << std::endl; // 0
    std::cout << b.id << std::endl; // 1
    std::cout << c.id << std::endl; // 2

    std::cout << Alfred::Utils::Counter<Bar>() << std::endl; // 0
    std::cout << Alfred::Utils::Counter<Bar>() << std::endl; // 1
    return 0;
}