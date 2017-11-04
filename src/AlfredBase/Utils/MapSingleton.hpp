#pragma once

#include <unordered_map>
#include "AlfredBase/Utils/NonCopyable.hpp"

namespace Alfred
{
    namespace Utils
    {
        template <typename K, typename T>
        struct MapSingleton : public NonCopyable
        {
            inline static T &getSingleton(K key)
            {
                static std::unordered_map<K, T> _singletonValue;
                return _singletonValue[key];
            }

            static T &get(K key)
            {
                return getSingleton(key);
            }
        };
    }
}