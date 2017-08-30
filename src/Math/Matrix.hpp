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
        { return "Bad line number for this matrix.\n"; }
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

    template <typename T>
    class Matrix
    {
    private:
        std::vector<std::vector<T>> _matrix;
        size_t _lines;
        size_t _cols;
        std::string _dim;

    public:
        Matrix(size_t LINES, size_t COLS) :
            _matrix(),
            _lines(LINES),
            _cols(COLS),
            _dim(std::to_string(LINES) + "x" + std::to_string(COLS))
        {
            if (LINES * COLS == 0)
                LOG.log(Logger::FATAL, "Can not make 0 sized matrix");
            _matrix.resize(LINES);
            for (size_t i = 0; i < LINES; ++i) {
                _matrix[i].resize(COLS);
            }
        }

        size_t getColsNumber() const
        {
            return _cols;
        }

        size_t getLinesNumber() const
        {
            return _lines;
        }

        const std::pair<size_t, size_t> getShape()
        {
            return std::pair<size_t, size_t>(_lines, _cols);
        };

        const std::vector<T> getLine(const size_t number)
        {
            std::vector<T> out;

            for (size_t i = 0; i < _cols; ++i) {
                out.push_back(_matrix[number][i]);
            }

            return out;
        };

        const std::vector<T> getCol(const size_t number)
        {
            std::vector<T> out;

            for (size_t i = 0; i < _lines; ++i) {
                out.push_back(_matrix[i][number]);
            }

            return out;
        };

        const std::string &getDim() const
        {
            return _dim;
        }

        const std::vector<T> flatten()
        {
            std::vector<T> out;

            for (const auto &line : _matrix)
                for (const auto &elem : line)
                    out.push_back(elem);
            return out;
        }

        Matrix &clear()
        {
            for (auto &line : _matrix)
                for (auto &elem : line)
                    elem = T();
            return *this;
        }

        Matrix &set(size_t line, size_t col, T elem)
        {
            if (line >= _lines)
                LOG.log(Alfred::Logger::FATAL,
                        "Matrix: Bad line " + std::to_string(line) + " while dimension is " + _dim + " -> " +
                        std::to_string(_lines));
            //TODO add custom exception

            if (col > _cols)
                LOG.log(Alfred::Logger::FATAL,
                        "Matrix: Too much element " + std::to_string(col) + " while dimension is " + _dim + " -> " +
                        std::to_string(_cols));
            //TODO add custom exception

            _matrix[line][col] = elem;
            return *this;
        }

        Matrix &set(size_t pos, T elem)
        {
            if (pos >= _lines * _cols)
                LOG.log(Logger::FATAL, "Bad position");
            //todo custom exception
            if (pos == 0)
            {
                _matrix[0][0] = elem;
                return *this;
            }
            size_t tmpi = pos / _cols;
            _matrix[tmpi][pos - tmpi * _cols] = elem;
            return *this;
        }

        const T get(size_t line, size_t col)
        {
            return _matrix[line][col];
        }

        const T get(size_t pos)
        {
            if (pos >= _lines * _cols)
                LOG.log(Logger::FATAL, "Bad position");
            //todo custom exception
            if (pos == 0)
                return _matrix[0][0];
            size_t tmpi = pos / _cols;
            return _matrix[tmpi][pos - tmpi * _cols];
        }

        template <typename ... Args>
        Matrix &setLine(size_t line, Args... src)
        {
            if (line >= _lines)
                LOG.log(Alfred::Logger::FATAL,
                        "Matrix: Bad line " + std::to_string(line) + " while dimension is " + _dim + " -> " +
                        std::to_string(_lines));
            //TODO add custom exception

            size_t col = 0;
            //TODO c'est immonde
            std::vector<T> tmp = {src...};
            if (tmp.size() > _cols)
                LOG.log(Alfred::Logger::FATAL,
                        "Matrix: Too much element " + std::to_string(tmp.size()) + " while dimension is " + _dim +
                        " -> " + std::to_string(_cols));
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

            if (tmp.size() < _lines * _cols)
                LOG.log(Alfred::Logger::FATAL, "Matrix: Bad Dimension while dimension is " + _dim);
            //TODO add custom exception

            size_t col = 0;
            size_t line = 0;
            while (line < _lines) {
                col = 0;
                while (col < _cols) {
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
            for (const auto &line : _matrix) {
                for (const auto &elem : line)
                    std::cout << elem << ", "; //todo not ", " at end line
                std::cout << std::endl;
            }

            return *this;
        }

        Matrix<T> &translate()
        {
            auto out = new Matrix<T>(_cols, _lines);

            size_t col = 0;
            size_t line = 0;

            while (line < _lines) {
                col = 0;
                while (col < _cols) {
                    out->set(col, line, _matrix[line][col]);
                    col++;
                }
                line++;
            }
            return *out;
        };

        const T multiplyDotLineCol(const std::vector<T> &one, const std::vector<T> &two)
        {
            T out = {};

            for (size_t i = 0; i < _cols; ++i) {
                out += one[i] * two[i];
            }
            return out;
        }

        Matrix &dot(Matrix<T> &other)
        {
            auto out = new Matrix<T>(this->getLinesNumber(), other.getColsNumber());

            if (_cols != other.getLinesNumber())
                throw MatrixBadShape(_dim, other.getDim(), std::string("dot product"));

            for (size_t i = 0; i < _lines; i++)
                for (size_t j = 0; j < other.getColsNumber(); j++)
                    out->set(i, j, multiplyDotLineCol(getLine(i), other.getCol(j)));

            return *out;
        }

        Matrix &reshape(size_t lines, size_t cols)
        {
            if (lines * cols == 0)
                LOG.log(Logger::FATAL, "Can not make 0 sized matrix");
            //todo exception
            std::vector<std::vector<T>> out;
            out.resize(lines);
            for (size_t i = 0; i < lines; ++i) {
                out[i].resize(cols);
            }
            for (auto &line : out)
                for (auto &elem : line)
                    elem = T();

            auto tmp = flatten();
            size_t tmpi;
            out[0][0] = tmp[0];
            for (size_t i = 1; i < tmp.size() && i < lines * cols; ++i) {
                {
                    tmpi = i / cols;
                    out[tmpi][i - tmpi * cols] = tmp[i];
                }
            }
            _matrix = out;
            _cols = cols;
            _lines = lines;
            _dim = std::to_string(_lines) + "x" + std::to_string(_cols);

            return *this;
        }

        template <typename X>
        Matrix<T> operator*(X x)
        {
            for (size_t i = 0; i < _lines; ++i) {
                for (size_t j = 0; j < _cols; ++j) {
                    _matrix[i][j] *= x;
                }
            }
            return *this;
        }

        Matrix<T> operator*(Matrix<T> x)
        {
            return this->dot(x);
        }

        template <typename X>
        Matrix<T> operator+(X x)
        {
            for (size_t i = 0; i < _lines; ++i) {
                for (size_t j = 0; j < _cols; ++j) {
                    _matrix[i][j] += x;
                }
            }
            return *this;
        }

        Matrix<T> operator+(Matrix<T> x)
        {
            if (getShape() != x.getShape())
                throw MatrixBadShape(_dim, x.getDim(), "addition");
            for (size_t i = 0; i < _lines; ++i) {
                for (size_t j = 0; j < _cols; ++j) {
                    _matrix[i][j] += x.get(i, j);
                }
            }
            return *this;
        }
    }; //Class Matrix
} //Namespace Alfred

#endif //ALFRED_MATRIX_HPP
