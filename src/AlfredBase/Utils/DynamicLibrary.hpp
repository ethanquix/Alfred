#pragma once

#include <string>
#include <dlfcn.h>

namespace Alfred
{
        namespace Utils
        {
            class DynamicLibrary
            {
              public:
                explicit DynamicLibrary(const std::string &lib, int openMode = RTLD_LAZY)
                {
                    _handle = dlopen(lib.c_str(), openMode);
                }

                virtual ~DynamicLibrary();

                bool isLoaded() const
                {
                    return _handle != nullptr;
                }

                template<typename T>
                T getSymbol(const std::string &symName)
                {
                    if (!_handle)
                        return nullptr;
                    return (T) dlsym(_handle, symName.c_str());
                }

              private:
                void *_handle;
            };
    }
}

