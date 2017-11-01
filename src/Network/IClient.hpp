/*
** IClient.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/IClient.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Sep 08 15:55:35 2017 Dimitri Wyzlic
** Last update Fri Sep 08 15:55:35 2017 Dimitri Wyzlic
*/

#pragma once

#include <functional>
#include <exception>
#include "config.hpp"

namespace Alfred
{
    namespace Network
    {
        struct ClientInfo
        {
            unsigned port;
            std::string ip;
            unsigned id;
        };

        class IClient
        {
          public:
            virtual ~IClient() = default;
            virtual IClient &Connect() = 0;
            virtual IClient &Connect(unsigned port) = 0;
            virtual IClient &Connect(const std::string &ip, unsigned port) = 0;
            virtual IClient &Send(void *msg, unsigned size) = 0;
            virtual IClient &Listen() = 0;
            virtual IClient &AsyncListen() = 0;
            virtual IClient &setOnReceived() = 0;
            virtual IClient &setTransferDataCallback(const std::function<void(IClient *, void *, unsigned)> &func) = 0;
            virtual IClient &transferData(IClient *, void *, unsigned) = 0;
            virtual IClient &setOnDisconnect(std::function<void(const std::string &, unsigned id)> func) = 0;
            virtual IClient &Stop() = 0;
            virtual IClient &setBufferSize(unsigned) = 0;
            virtual ClientInfo &getInfos() = 0;
            virtual IClient &waitUntilDisconnect() = 0;
        };
    }
}
