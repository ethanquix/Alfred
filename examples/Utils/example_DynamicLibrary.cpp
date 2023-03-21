#include <Alfred/Utils/DynamicLibrary.hpp>

int main()
{
    std::string libExtension = Alfred::Utils::getOSDynLibExtension();

    std::cout << "Lib end with " << libExtension << std::endl;

    typedef char const *(*libFunction)();

    Alfred::Utils::LibLoader<libFunction> loader;

    libFunction lf = loader.getSymbol("liblocation/mylib" + libExtension);

    lf();

    return 0;
}