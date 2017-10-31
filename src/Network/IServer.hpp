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

#include <unordered_map>
#include <unordered_map>
#include <functional>
#include <netinet/in.h>
#include "IClient.hpp"
#include "AsyncUnorderedMap.hpp"

namespace Alfred
{
    namespace Network
    {
        class IServer
        {
          public:
            virtual ~IServer() = default;
            virtual Async::AsyncUnorderedMap<int, IClient *> &getClients() = 0;
            virtual IServer &onConnect(const std::function<void(IServer *, int clientFD)> &_func) = 0;
            virtual IServer &onDisconnect(const std::function<void(IServer *, int clientFD)> &_func) = 0;
            virtual IClient &getClientInfo(int clientID) = 0;
            virtual IServer &run() = 0;
            virtual IServer &asyncRun() = 0;
            virtual IServer &stop() = 0;
            virtual IServer &setClientBuilder(const std::function<IClient *(struct sockaddr_in in, unsigned fd)> &func) = 0;
            virtual IServer &clientDeleted(unsigned id) = 0;
            virtual IClient &operator[](int id) = 0;
        };
    }
}

#endif //ALFRED_ISERVER_HPP
