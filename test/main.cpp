#include <gtest/gtest.h>

#include "AlfredBase/Serializer/Serializer.hpp"

int main()
{
    YOLO y;

    std::string output;

    y >> output;

    std::cout << output << std::endl;

    y.setX("NE M'AFFICHE PAS STP");

    output >> y;

    std::cout << y << std::endl;
}

//int main(int ac, char **av)
//{
//    testing::InitGoogleTest(&ac, av);
//    return RUN_ALL_TESTS();
//}