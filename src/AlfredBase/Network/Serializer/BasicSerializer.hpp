#pragma once

#include <ISerializer.hpp>
#include <Logger.hpp>

namespace Alfred
{
    template <class T, typename S>
    class BasicSerializer : protected ISerializer<T, S>
    {
    public:

        S serialize(T data, S to) override
        {
            to = reinterpret_cast<S>(data);
            return to;
        }

        T deserialize(T to, S from) override
        {
            to = reinterpret_cast<T>(from);
            return to;
        }
    };
}