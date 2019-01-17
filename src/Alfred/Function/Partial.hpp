#pragma once

#include <utility>
#include <tuple>
#include <cstddef>
#include <type_traits>

namespace Alfred
{
    namespace Function
    {
        template <typename Func, typename ...Args>
        class Partial
        {
        private:
            Func &&_func;
            std::tuple<Args...> _args;
        public:
            Partial(Func &&func, Args ...args) :
                _func(std::forward<Func>(func)),
                _args(std::forward<Args>(args)...)
            {}

            auto operator()()
            {
                return std::apply(_func, _args);
            }

            template <typename ...CompArgs>
            auto operator()(CompArgs ...compArgs)
            {
                std::tuple<Args...> tupleCompArgs(std::forward<Args>(compArgs)...);

                return std::apply(_func, std::tuple_cat(_args, tupleCompArgs));
            }
        };

        template <typename Func, typename ...Args>
        Partial<Func, Args...> partial(Func &&func, Args ...args)
        {
            return Partial<Func, Args...>(func, args...);
        };

    }
}

