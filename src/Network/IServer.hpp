/*
** IServer.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/IServer.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Sep 08 15:56:04 2017 Dimitri Wyzlic
** Last update Fri Sep 08 15:56:04 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_ISERVER_HPP
#define ALFRED_ISERVER_HPP

#include "INetwork.hpp"

namespace Alfred
{
    class IServer : protected INetwork
    {
    public:
        virtual void run() = 0;
    };
}

#endif //ALFRED_ISERVER_HPP
