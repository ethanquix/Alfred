#pragma once

namespace Alfred
{
    template <class T, typename S>
    class ISerializer
    {
    public:
        virtual S serialize(T data, S to) = 0;

        virtual T deserialize(T to, S from) = 0;

    };
}