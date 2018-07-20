#include "AlfredBase/Function/Partial.hpp"
#include "AlfredBase/Logger/Logger.hpp"

int add(int a, int b)
{
    return a + b;
}

int main()
{
    LOG_SET_CONSOLE;

    auto toujoursQuatre = Alfred::Function::partial(add, 1, 3);
    auto deuxPlus = Alfred::Function::partial(add, 2);

    int quatre = toujoursQuatre();
    int vingt = deuxPlus(18);

    LOG_WARNING << quatre << LOG_ENDL; // 4
    LOG_WARNING << vingt << LOG_ENDL; // 20

    return 0;
}