/*
** InfiniteList.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/InfiniteList.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu Aug 31 20:24:02 2017 Dimitri Wyzlic
** Last update Thu Aug 31 20:24:02 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_INFINITELIST_HPP
#define ALFRED_INFINITELIST_HPP

#include <vector>
#include <functional>
#include <Logger.hpp>
#include <ostream>

namespace Alfred
{
    class InfiniteListNoNextFunction : public std::exception
    {
        const char *what() const throw() override
        { return "You need to set a next function before you can access a not yet calculated element.\n"; }
    };

    template <typename T>
    class InfiniteList
    {
    private:
        std::vector<T> _list;
        std::function<T(InfiniteList<T> &)> _next;
        std::function<T(T elem)> _map;

    public:
        InfiniteList(const T &first = T()) :
            _list(),
            _next(nullptr),
            _map(nullptr)
        {
            _list.push_back(first);
        }

        InfiniteList<T> &setNextFunc(std::function<T(InfiniteList<T> &)> func)
        {
            _next = std::move(func);
            return *this;
        }

        T &get(size_t pos)
        {
            if (_next == nullptr)
                throw InfiniteListNoNextFunction();
            while (_list.size() <= pos)
                _list.push_back(_next(*this));
            return _list[pos];
        }

        T &last()
        { return _list[_list.size() - 1]; }

        T &next()
        {
            _list.push_back(_next(*this));
            return _list[_list.size() - 1];
        }

        const size_t max() const
        { return _list.size() - 1; }

        const size_t size() const
        { return _list.size(); }

        std::vector<T> flatten() const
        { return _list; }

        InfiniteList<T> &print()
        {
            std::cout << "max: " << std::to_string(max()) << std::endl;
            auto &last = *(--_list.end());
            for (const auto &elem : _list) {
                std::cout << elem;
                if (&elem != &last)
                    std::cout << " ";
            }
            std::cout << std::endl;
            return *this;
        }

        T &operator[](const size_t pos)
        {
            return get(pos);
        }

        InfiniteList<T> &operator++()
        {
            next();
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const InfiniteList &list)
        {
            os << "max: " << std::to_string(list.max()) << std::endl;
            auto l = list.flatten();
            auto &last = *(--l.end());
            for (const auto &elem : l) {
                os << elem;
                if (&elem != &last)
                    os << " ";
            }
            os << std::endl;
            return os;
        }

        InfiniteList<T> operator++(int)
        {
            next();
            return *this;
        }

        InfiniteList<T> &map(std::function<T(T elem)> func)
        {
            _map = func;
            return *this;
        }

        InfiniteList<T> &limit(size_t x)
        {
            get(x - 1);
            for (size_t i = 0; i < x; ++i) {
                _list[i] = _map(_list[i]);
            }
            return *this;
        }

        T sum()
        {
            T out = {};
            for (auto &elem : _list)
                out = out + elem;
            return out;
        }
    }; //Class InfiniteList
} //Namespace Alfred;

#endif //ALFRED_INFINITELIST_HPP
