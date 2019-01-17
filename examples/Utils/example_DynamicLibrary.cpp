#include <Alfred/Utils/DynamicLibrary.hpp>

int main()
{
    std::string libExtension = Alfred::Utils::getOSDynLibExtension();

    std::cout << "Lib end with " << libExtension << std::endl;

    typedef typedef char const *(*libFunction)();

    Alfred::Utils::LibLoader<libFunction> loader;

    libFunction lf = loader.getSymbol("liblocation/mylib" + libExtension);

    return 0;
}