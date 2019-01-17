#include <gtest/gtest.h>

#include "Alfred/Logger/Logger.hpp"

int main(int ac, char **av)
{
    LOG_SET_CONSOLE;

    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}