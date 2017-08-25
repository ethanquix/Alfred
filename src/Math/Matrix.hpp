/*
** Matrix.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/Matrix.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Aug 23 20:02:18 2017 Dimitri Wyzlic
** Last update Wed Aug 23 20:02:18 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_MATRIX_HPP
#define ALFRED_MATRIX_HPP

#include "Logger.hpp"

#include <array>
#include <vector>

namespace Alfred
{
    class MatrixBadLine : public std::exception
    {
        const char *what() const throw() override
        { return "Checkpoint already exist.\n"; }
    };

    template <typename T, size_t COLS, size_t LINES>
    class Matrix
    {
    private:
        std::array<std::array<T, COLS>, LINES> _matrix;
        size_t _cols;
        size_t _lines;
        std::string _dim;

    public:
        Matrix() :
            _matrix(),
            _cols(COLS),
            _lines(LINES),
            _dim(std::to_string(COLS) + "x" + std::to_string(LINES))
        {}

        Matrix &clear()
        {
            for (auto &line : _matrix)
                for (auto &elem : line)
                    elem = T();
            return *this;
        }
        Matrix &set(size_t col, size_t line, T elem)
        {
            if (line >= _lines)
                LOG.log(Alfred::Logger::FATAL, "Matrix: Bad line " + std::to_string(line) + " while dimension is " + _dim + " -> " + std::to_string(_lines));
            //TODO add custom exception

            if (col > _cols)
                LOG.log(Alfred::Logger::FATAL, "Matrix: Too much element " + std::to_string(col) + " while dimension is " + _dim + " -> " + std::to_string(_cols));
            //TODO add custom exception

            _matrix[line][col] = elem;
            return *this;
        }

        template <typename ... Args>
        Matrix &setLine(size_t line, Args... src)
        {
            if (line >= _lines)
                LOG.log(Alfred::Logger::FATAL, "Matrix: Bad line " + std::to_string(line) + " while dimension is " + _dim + " -> " + std::to_string(_lines));
            //TODO add custom exception

            size_t col = 0;
            //TODO c'est immonde
            std::vector<T> tmp = {src...};
            if (tmp.size() > _cols)
                LOG.log(Alfred::Logger::FATAL, "Matrix: Too much element " + std::to_string(tmp.size()) + " while dimension is " + _dim + " -> " + std::to_string(_cols));
            //TODO add custom exception
            for (const auto &it : tmp)
                _matrix[line][col++] = it;
            return *this;
        };

        template <typename ... Args>
        Matrix &setMatrix(Args... src)
        {
            clear();
            std::vector<T> tmp = {src...};
            //TODO c'est immonde

            if (tmp.size() >= _lines * _cols)
                LOG.log(Alfred::Logger::FATAL, "Matrix: Bad Dimension while dimension is " + _dim);
            //TODO add custom exception

            size_t col = 0;
            size_t line = 0;
            while (line < _lines)
            {
                col = 0;
                while (col < _cols)
                {
                    _matrix[line][col] = tmp[line * _cols + col];
                    col++;
                }
                line++;
            }
            return *this;
        };

        Matrix &print()
        {
            std::cout << "Matrix: " << _dim << std::endl;
            for (const auto &line : _matrix)
            {
                for (const auto &elem : line)
                    std::cout << elem << ", "; //todo not ", " at end line
                std::cout << std::endl;
            }

            return *this;
        }

        Matrix<T, LINES, COLS> &translate()
        {
            auto out = new Matrix<T, LINES, COLS>;

            size_t col = 0;
            size_t line = 0;

            while (line < _lines)
            {
                col = 0;
                while (col < _cols)
                {
                    out->set(line, col, _matrix[line][col]);
                    col++;
                }
                line++;
            }
            return *out;
        };

        Matrix &dot(const Matrix &other)
        {
            auto out = new Matrix<T, LINES, COLS>;

            //todo

            return *out;
        }

    }; //Class Matrix
} //Namespace Alfred

#endif //ALFRED_MATRIX_HPP
