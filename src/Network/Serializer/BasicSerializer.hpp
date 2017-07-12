/*
** BasicSerializer.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/BasicSerializer.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Jul 12 20:21:13 2017 Dimitri Wyzlic
** Last update Wed Jul 12 20:21:13 2017 Dimitri Wyzlic
*/

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