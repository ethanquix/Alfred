/*
** UnixServer.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/UnixServer.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Sep 08 16:12:28 2017 Dimitri Wyzlic
** Last update Fri Sep 08 16:12:28 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_UNIXSERVER_HPP
#define ALFRED_UNIXSERVER_HPP

#include "IServer.hpp"

namespace Alfred
{
    class UnixServer : protected IServer
    {
    public:
        explicit UnixServer(int port)
        {
        }

        UnixServer(int ip, int port)
        {
        }

        INetwork &send(const ConnectionMode &mode, const char *msg) override
        {
            return <#initializer#>;
        }

        INetwork &receive() override
        {
            return <#initializer#>;
        }

        void run() override
        {
        }
    };
}

#endif //ALFRED_UNIXSERVER_HPP
