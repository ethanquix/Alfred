#pragma once

#include "AlfredBase/Logger/Logger.hpp"
#include "AlfredBase/Math/MatrixException.hpp"

#include <array>
#include <vector>
#include <ostream>

namespace Alfred
{
    namespace Matrix
    {
        template <typename T>
        class Matrix
        {
          private:
            std::vector<std::vector<T>> _matrix;
            size_t _lines;
            size_t _cols;
            std::string _dim;

          public:
            Matrix(size_t LINES = 1, size_t COLS = 1) :
                _matrix(),
                _lines(LINES),
                _cols(COLS),
                _dim(std::to_string(LINES) + "x" + std::to_string(COLS))
            {
                if (LINES * COLS == 0)
                    LOG.log(Logger::LOG_FATAL, "Can not make 0 sized matrix");
                _matrix.resize(LINES);
                for (size_t i = 0; i < LINES; ++i) {
                    _matrix[i].resize(COLS);
                }
            }

            size_t getColsNumber() const
            { return _cols; }

            size_t getLinesNumber() const
            { return _lines; }

            const std::pair<size_t, size_t> getShape() const
            { return std::pair<size_t, size_t>(_lines, _cols); };

            const std::vector<T> getLine(const size_t number) const
            {
                std::vector<T> out;

                for (size_t i = 0; i < _cols; ++i) {
                    out.push_back(_matrix[number][i]);
                }

                return out;
            };

            const std::vector<T> getCol(const size_t number) const
            {
                std::vector<T> out;

                for (size_t i = 0; i < _lines; ++i) {
                    out.push_back(_matrix[i][number]);
                }

                return out;
            };

            const std::string &getDim() const
            { return _dim; }

            const std::vector<T> flatten() const
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
                    throw MatrixOutOfBounds(line, _lines, "row");
                if (col > _cols)
                    throw MatrixOutOfBounds(col, _cols, "col");

                _matrix[line][col] = elem;
                return *this;
            }

            Matrix &set(size_t pos, T elem)
            {
                if (pos >= _lines * _cols)
                    throw MatrixOutOfBounds(pos, _lines * _cols, "lit. pos");
                if (pos == 0) {
                    _matrix[0][0] = elem;
                    return *this;
                }
                size_t tmpi = pos / _cols;
                _matrix[tmpi][pos - tmpi * _cols] = elem;
                return *this;
            }

            const T get(size_t line, size_t col) const
            {
                if (line >= _lines)
                    throw MatrixOutOfBounds(line, _lines, "row");
                if (col > _cols)
                    throw MatrixOutOfBounds(col, _cols, "col");
                return _matrix[line][col];
            }

            const T get(size_t pos) const
            {
                if (pos >= _lines * _cols)
                    throw MatrixOutOfBounds(pos, _lines * _cols, "lit. pos");
                if (pos == 0)
                    return _matrix[0][0];
                size_t tmpi = pos / _cols;
                return _matrix[tmpi][pos - tmpi * _cols];
            }

            template <typename ... Args>
            Matrix &setLine(size_t line, Args... src)
            {
                if (line >= _lines)
                    throw MatrixOutOfBounds(line, _lines, "row");

                std::vector<T> tmp = {src...};
                if (tmp.size() > _cols)
                    throw MatrixOutOfBounds(tmp.size(), _cols, "col");

                size_t col = 0;
                for (const auto &it : tmp)
                    _matrix[line][col++] = it;
                return *this;
            };

            template <typename ... Args>
            Matrix &setMatrix(Args... src)
            {
                clear();
                std::vector<T> tmp = {src...};

                if (tmp.size() < _lines * _cols)
                    throw MatrixOutOfBounds(tmp.size(), _lines * _cols, "lit. pos");

                for (size_t line = 0; line < _lines; ++line) {
                    for (size_t col = 0; col < _cols; ++col) {
                        _matrix[line][col] = tmp[line * _cols + col];
                    }
                }
                return *this;
            };

            Matrix &print()
            {
                std::cout << "Matrix: " << _dim << std::endl;
                for (const auto &line : _matrix) {
                    auto &last = *(--line.end());
                    for (const auto &elem : line) {
                        std::cout << elem;
                        if (&elem != &last)
                            std::cout << " ";
                    }
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

            const T multiplyDotLineCol(const std::vector<T> &one, const std::vector<T> &two) const
            {
                T out = {};

                for (size_t i = 0; i < _cols; ++i) {
                    out += one[i] * two[i];
                }
                return out;
            }

            const T multiplyDotColLine(const std::vector<T> &one, const std::vector<T> &two) const
            {
                T out = {};

                for (size_t i = 0; i < _lines; ++i) {
                    out += one[i] * two[i];
                }
                return out;
            }

            template <typename X>
            Matrix<T> &dot(const std::vector<X> &other)
            {
                auto out = new Matrix<T>(this->getLinesNumber(), 1);

                if (_cols != other.size())
                    throw MatrixBadShape(_dim, std::to_string(other.size()) + "x1", std::string("dot product"));

                for (size_t i = 0; i < _lines; i++)
                {
                    out->set(i, 0, multiplyDotLineCol(getLine(i), other));
                }
                return *out;
            }

            Matrix<T> &dot(T &other)
            {
                auto out = new Matrix<T>(this->getLinesNumber(), 1);

                if (_cols != 1)
                    throw MatrixBadShape(_dim, other.getDim(), std::string("dot product"));

                for (size_t i = 0; i < _lines; i++)
                        out->set(i, 0, multiplyDotLineCol(getLine(i), other));

                return *out;
            }

            Matrix<T> &dot(Matrix<T> &other)
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
                    throw BadMatrixSize(std::to_string(lines) + "x" + std::to_string(cols));
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

            Matrix(const std::vector<T> &x)
            {
                _cols = x.size();
                _lines = 1;
                _dim = std::to_string(_lines) + "x" + std::to_string(_cols);

                _matrix.resize(1);
                _matrix[0].resize(x.size());

                size_t i = 0;
                for (const auto &it : x)
                {
                    _matrix[0][i] = it;
                    i += 1;
                }
            }

            Matrix<T> &operator=(const std::vector<T> &x)
            {
                _cols = x.size();
                _lines = 1;
                _dim = std::to_string(_lines) + "x" + std::to_string(_cols);

                _matrix.resize(1);
                _matrix[0].resize(x.size());

                size_t i = 0;
                for (const auto &it : x)
                {
                    _matrix[0][i] = it;
                    i += 1;
                }

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
            { return this->dot(x); }

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

            Matrix<T> operator+(const Matrix<T> &x)
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

            Matrix<T> operator+=(const Matrix<T> &x)
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

            template <typename X>
            Matrix<T> operator-(X x)
            {
                for (size_t i = 0; i < _lines; ++i) {
                    for (size_t j = 0; j < _cols; ++j) {
                        _matrix[i][j] -= x;
                    }
                }
                return *this;
            }

            Matrix<T> operator-(Matrix<T> x)
            {
                if (getShape() != x.getShape())
                    throw MatrixBadShape(_dim, x.getDim(), "addition");
                for (size_t i = 0; i < _lines; ++i) {
                    for (size_t j = 0; j < _cols; ++j) {
                        _matrix[i][j] -= x.get(i, j);
                    }
                }
                return *this;
            }

            template <typename X>
            Matrix<T> operator/(X x)
            {
                for (size_t i = 0; i < _lines; ++i) {
                    for (size_t j = 0; j < _cols; ++j) {
                        _matrix[i][j] /= x;
                    }
                }
                return *this;
            }

            Matrix<T> operator/(Matrix<T> x)
            {
                if (getShape() != x.getShape())
                    throw MatrixBadShape(_dim, x.getDim(), "addition");
                for (size_t i = 0; i < _lines; ++i) {
                    for (size_t j = 0; j < _cols; ++j) {
                        _matrix[i][j] /= x.get(i, j);
                    }
                }
                return *this;
            }

            std::vector<T> &operator[](const size_t line)
            {
                if (line >= _lines)
                    throw MatrixOutOfBounds(line, _lines, "line");
                return _matrix[line];
            }

            friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
            {
                os << "Matrix: " << matrix.getDim() << std::endl;
                size_t lines = matrix.getLinesNumber();
                for (size_t i = 0; i < lines; ++i) {
                    auto line = matrix.getLine(i);
                    auto &last = *(--line.end());
                    for (const auto &elem : line) {
                        os << elem;
                        if (&elem != &last)
                            os << " ";
                    }
                    os << std::endl;
                }
                return os;
            }
        }; //Class Matrix

        template <typename T>
        std::vector<T> dot(const std::vector<T> &v, const Matrix<T> &m)
        {
            std::vector<T> out;
            out.resize(m.getColsNumber());

            if (v.size() != m.getLinesNumber())
                throw MatrixBadShape(std::to_string(v.size()), m.getDim(), std::string("dot product"));

            for (size_t i = 0; i < m.getColsNumber(); i++)
            {
                out[i] = m.multiplyDotColLine(v, m.getCol(i));
            }
            return out;
        }
    }
} //Namespace Alfred
