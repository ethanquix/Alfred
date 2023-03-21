#pragma once

#pragma once

#ifdef WIN32
#include <windows.h>
#include "mon_dirent.hpp"
#else

#include <dlfcn.h>
#include <dirent.h>

#endif

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include "FindOS.hpp"
#include <Alfred/Utils/NonCopyable.hpp>
#include <unordered_map>
#include "Alfred/Logger/Logger.hpp"
#include <type_traits>
#include <stdio.h>
#include <string>
#include <dlfcn.h>

namespace Alfred
{
    namespace Utils
    {
        static std::string getOSDynLibExtension()
        {
            if constexpr (the_os == OS::Linux)
                return ".so";
            else if constexpr (the_os == OS::Mac)
                return ".dylib";
            else
                return ".dll";
        }

        template <typename T>
        class LibLoader : public Alfred::Utils::NonCopyable
        {
        private:
            std::string _osLibEnding;

        public:
            T getSymbol(const std::string &path)
            {
#ifdef WIN32
                HINSTANCE hGetProcIDDLL = LoadLibrary(path.c_str());
      if (!hGetProcIDDLL) {
          LOG_ERROR << "could not load the dynamic library" << std::endl;
          return nullptr;
      }

      T tmp = (T) GetProcAddress(hGetProcIDDLL, "getSymbol");
      if (tmp == NULL)
      {
            LOG_ERROR << "Failed to load lib" << GetLastError() << " " << path << std::endl;
            return nullptr;
      }
      return tmp;
#else
                void *handle = dlopen(path.c_str(), RTLD_LAZY);
                char *lError = dlerror();
                if (lError) {
                    LOG_ERROR << "Error while loading lib symbol " << path << " " << lError << std::endl;
                    return nullptr;
                }
                return (T)(dlsym(handle, "getSymbol"));
#endif
            }

            LibLoader() :
                _osLibEnding(getOSDynLibExtension())
            {}
        };
    }
}
