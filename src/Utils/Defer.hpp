#pragma once

#include <functional>

#define TOKENPASTE_(x, y) x ## y
#define TOKENPASTE(x, y) TOKENPASTE_(x, y)
#define DEFER(X) Alfred::Utils::Defer TOKENPASTE(RANDOM_NAME_FOR_DEFER_, __COUNTER__)(X)

namespace Alfred
{
    namespace Utils
    {
        class Defer
        {
          private:
            std::function<void()> _func;

          public:
            explicit Defer(std::function<void()> _func)
            { this->_func = _func; }

            virtual ~Defer()
            { _func(); }
        };
    }
}

