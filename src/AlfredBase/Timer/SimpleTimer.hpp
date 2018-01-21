#pragma once

#include <chrono>

namespace Alfred
{
    namespace Time
    {
        class SimpleTimer
        {
          private:
            std::chrono::time_point<std::chrono::system_clock> _time;

          public:
            SimpleTimer() :
                _time(std::chrono::system_clock::now())
            {}

            void restart()
            {
                _time = std::chrono::system_clock::now();
            }

            double elapsed()
            {
                return std::chrono::duration<double>(std::chrono::system_clock::now() - _time).count();
            }
        };
    }
}

