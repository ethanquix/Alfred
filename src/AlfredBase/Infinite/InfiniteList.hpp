#pragma once

//WARNING
//It may look like a functional streams implementation but it's not
//I am currently working on a functionnal streams implementation
//But this is just an experimentation

#include "AlfredBase/Logger/Logger.hpp"
#include <vector>
#include <functional>
#include <ostream>
#include <queue>

namespace Alfred
{
    namespace Infinite
    {
        class InfiniteListNoNextFunction : public std::exception
        {
            const char *what() const throw() override
            { return "You need to set a next function before you can access a not yet calculated element.\n"; }
        };

        enum InfiniteListOperator
        {
            ILO_MAP,
            ILO_FILTER
        };

        template <typename T>
        class InfiniteList
        {
          private:
            std::vector<T> _list;
            std::function<T(InfiniteList<T> &)> _next;
            std::deque<std::function<T(T elem)>> _map;
            std::deque<std::function<bool(T)>> _filter;
            std::deque<enum InfiniteListOperator> _todo;
            size_t _idx;

          public:
            InfiniteList(const T &first = T()) :
                _list(),
                _next(nullptr),
                _map(),
                _filter(),
                _todo(),
                _idx(0)
            {
                _list.push_back(first);
            }

            InfiniteList(const std::vector<T> &from) :
                _list(),
                _next(nullptr),
                _map(),
                _filter(),
                _todo(),
                _idx(0)
            {
                _list = from;
            }

          private:
            InfiniteList<T> &__execute()
            {
                while (!_todo.empty()) {
                    if (_todo.front() == ILO_MAP) {
                        for (size_t i = 0; i < _list.size(); ++i) {
                            _list[i] = _map.front()(_list[i]);
                        }
                        _map.pop_front();
                    } else if (_todo.front() == ILO_FILTER) {
                        std::vector<T> _new = {};

                        for (const auto &it : _list) {
                            if (_filter.front()(it))
                                _new.push_back(it);
                        }
                        _list = _new;
                        _filter.pop_front();
                    }
                    _todo.pop_front();
                }
                return *this;
            }

          public:

            InfiniteList<T> &set(const T &elem, const size_t idx)
            {
                this->get(idx + 1);
                this->_list[idx] = elem;
                return *this;
            }

            InfiniteList<T> &setNext(const T &elem)
            {
                this->_list.push_back(elem);
                return *this;
            }

            const size_t getIdx() const
            {
                return _idx;
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
                while (_list.size() <= pos) {
                    _idx = _list.size();
                    _list.push_back(_next(*this));
                }
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

            std::vector<T> flatten()
            {
                __execute();
                return _list;
            }

            InfiniteList<T> &print()
            {
                std::cout << std::to_string(size()) << "elem" << std::endl;
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
            { return get(pos); }

            InfiniteList<T> &operator++()
            {
                next();
                return *this;
            }

            friend std::ostream &operator<<(std::ostream &os, InfiniteList &list)
            {
                os << std::to_string(list.size()) << "elem" << std::endl;
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

            InfiniteList<T> &map(std::function<T(T elem)> &&func)
            {
                _map.push_back(func);
                _todo.push_back(ILO_MAP);
                return *this;
            }

            template<typename Fctor>
            auto map_to(Fctor func, size_t max)
            {
                std::vector<decltype(func({}))> list;

                get(max - 1);

                for (const auto &elem : _list)
                    if (max-- == 0)
                        break;
                    else
                        list.push_back(func(elem));

                auto out = new InfiniteList<decltype(func({}))>(list);
                return *out;
            }

            InfiniteList<T> &limit(size_t x)
            {
                get(x - 1);
                _list.resize(x);

                __execute();

                return *this;
            }

            T sum()
            {
                T out = {};
                for (auto &elem : _list)
                    out = out + elem;
                return out;
            }

            InfiniteList<T> &filter(std::function<bool(T)> func)
            {
                _filter.push_back(func);
                _todo.push_back(ILO_FILTER);

                return *this;
            }

            InfiniteList<T> &end()
            {
                __execute();

                return *this;
            }

            InfiniteList<T> &enumerate(std::function<bool(T)> func)
            {
                size_t i = 0;
                std::vector<T> out;
                size_t precSize = 0;
                bool stop;

                while (true) {
                    stop = false;
                    get(i);
                    out.push_back(_list[i]);

                    auto save_map = _map;
                    auto save_filter = _filter;

                    for (const auto &todo : _todo) {
                        if (stop)
                            break;
                        switch (todo) {
                            case ILO_MAP:
                                out.back() = _map.front()(out.back());
                                _map.pop_front();
                                break;
                            case ILO_FILTER:
                                if (!_filter.front()(out.back())) {
                                    out.pop_back();
                                    stop = true;
                                    continue;
                                }
                                _filter.pop_front();
                                break;
                        }
                    }
                    _map = save_map;
                    _filter = save_filter;

                    if (!stop && precSize != out.size() && func(out.back())) {
                        out.pop_back();
                        _list = out;
                        _map.clear();
                        _filter.clear();
                        _todo.clear();
                        return *this;
                    }
                    precSize = out.size();
                    i++;
                }
            }

            const std::vector<T> &extract()
            {
                return _list;
            }

            const unsigned long count()
            {
                __execute();
                return _list.size();
            }
        }; //Class Infinite
    }
} //Namespace Alfred;
