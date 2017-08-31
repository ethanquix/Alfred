/*
** testMath.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testMath.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Aug 23 20:00:33 2017 Dimitri Wyzlic
** Last update Wed Aug 23 20:00:33 2017 Dimitri Wyzlic
*/

#include "Math.hpp"

int main()
{
    Alfred::Matrix<int> a(2, 3);
    Alfred::Matrix<Alfred::Matrix<int>> c(2, 3);
    a.setMatrix(1, 2, 3, 4, 5, 6);

    Alfred::Matrix<int> b(3, 2);
    b.setMatrix(7, 8, 9, 10, 11, 12);


//    a.print();
//    std::cout << c;
    std::cout << a;
    std::cout << a[1][1];
//    b.print();
//
//    auto f = a.dot(b).print().flatten();
//
//    for (const auto &elem : f)
//        std::cout << elem << std::endl;
//    a.reshape(10, 1).print();
//    a = a + a;
//    a.print();
}