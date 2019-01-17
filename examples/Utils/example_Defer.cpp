#include <iostream>
#include <fstream>

#include <Alfred/Utils/Defer.hpp>

int main()
{
    std::ofstream myfile;

    myfile.open("test.txt");
    DEFER([&] () { myfile.close(); });

    //Do stuff with file

    return 0;
}