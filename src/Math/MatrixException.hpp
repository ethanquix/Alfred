/*
** MatrixException.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/MatrixException.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu Aug 31 20:19:02 2017 Dimitri Wyzlic
** Last update Thu Aug 31 20:19:02 2017 Dimitri Wyzlic
*/

#pragma once

#include <exception>
#include <string>

namespace Alfred
{
    namespace Matrix
    {
        class MatrixBadLine : public std::exception
        {
            const char *what() const throw() override
            { return "Bad line number for this matrix.\n"; }
        };

        class BadMatrixSize : public std::exception
        {
            std::string msg;
          public:
            BadMatrixSize(const std::string &size) :
                msg(std::string("Bad Matrix size:  ") + size)
            {}

            virtual const char *what() const throw()
            { return msg.c_str(); }
        };

        class MatrixOutOfBounds : public std::exception
        {
            std::string msg;
          public:
            MatrixOutOfBounds(const size_t &pos, const size_t &max, const std::string &loc) :
                msg(std::string("Cant access this location ") + std::to_string(pos) + loc +
                    std::string(" while maximum is") + std::to_string(max))
            {}

            virtual const char *what() const throw()
            { return msg.c_str(); }
        };

        class MatrixBadShape : public std::exception
        {
            std::string msg;
          public:
            MatrixBadShape(const std::string &dim1, const std::string &dim2, const std::string &op) :
                msg(std::string("Cant do this operation (") + op + std::string(") due to incorrect shape: ") + dim1 +
                    std::string(" ") + dim2)
            {}

            virtual const char *what() const throw()
            {
                return msg.c_str();
            }
        };
    }
}