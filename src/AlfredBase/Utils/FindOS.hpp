#pragma once

namespace Alfred
{
    namespace Utils
    {
        enum class OS
        {
            Linux, Mac, Windows
        };

#ifdef __linux__
        constexpr OS the_os = OS::Linux;
#elif __APPLE__
        constexpr OS the_os = OS::Mac;
#elif WIN32
constexpr OS the_os = OS::Windows;
#endif
    }
}

//Translate the macros to C++ at a single point in the application