//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______    
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\   
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____  
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\ 
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/ 

// SimpleTimer.hpp created 03/11/17

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

