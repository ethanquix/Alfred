#pragma once

#include <functional>

class Defer
{
  private:
    std::function<void()> _func;
  public:

    explicit Defer(std::function<void()> _func)
    {
        this->_func = _func;
    }

    virtual ~Defer()
    {
        _func();
    }
};

