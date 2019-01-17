#pragma once

#include "NonCopyable.hpp"

namespace Alfred
{
    namespace Utils
    {
        template <typename T>
        struct Singleton : public NonCopyable
        {
            inline static T &getSingleton()
            {
                static T _singletonValue;
                return _singletonValue;
            }

            static T &get()
            {
                return getSingleton();
            }
        };
    }
}