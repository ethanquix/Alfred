/*
** testMath.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testMath.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Aug 23 20:00:33 2017 Dimitri Wyzlic
** Last update Wed Aug 23 20:00:33 2017 Dimitri Wyzlic
*/

#include <gtest/gtest.h>
#include "Alfred/Math/Math.hpp"

TEST(Math, Matrix)
{
    Alfred::Matrix::Matrix<int> matrix(2, 2);
    matrix.setMatrix(1, 2, 3, 4);

    std::cout << matrix.dot(matrix) << std::endl;
}

TEST(Math, Fraction)
{
    auto a = Alfred::Math::MakeFraction(5, 3.14);
    auto b = Alfred::Math::MakeFraction(a, 4);
    std::cout << static_cast<float>(b) << std::endl; // -> 0.398089
}

//TODO