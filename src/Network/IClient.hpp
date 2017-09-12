/*
** IClient.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/IClient.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Sep 08 15:55:35 2017 Dimitri Wyzlic
** Last update Fri Sep 08 15:55:35 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_ICLIENT_HPP
#define ALFRED_ICLIENT_HPP

#include "INetwork.hpp"

namespace Alfred
{
    class IClient : protected INetwork
    {
    public:
        virtual void listen() = 0;
    };
}

#endif //ALFRED_ICLIENT_HPP
