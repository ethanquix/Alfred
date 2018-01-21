#pragma once

#include <functional>
#include <exception>

#ifdef _WIN32

#include <WinSock2.h>

#endif

#include "AlfredBase/config.hpp"

namespace Alfred
{
    namespace Network
    {
        struct ClientInfo
        {
            unsigned port;
            std::string ip;
#ifdef _WIN32
            SOCKET id;
#else
            unsigned id;

#endif
        };

        class IClient
        {
          public:
            //TODO add pipelines
            virtual ~IClient() = default;
            virtual IClient &Connect() = 0;
            virtual IClient &Connect(unsigned port) = 0;
            virtual IClient &Connect(const std::string &ip, unsigned port) = 0;
            virtual IClient &Send(void *msg, unsigned size) = 0;
            virtual IClient &SendTo(const std::string &ip, int port, void *msg, unsigned size) = 0;
            virtual IClient &Listen() = 0;
            virtual IClient &AsyncListen() = 0;
            virtual IClient &onNewMessage() = 0;
            virtual IClient &setTransferDataCallback(const std::function<void(IClient *, void *, unsigned)> &func) = 0;
            virtual IClient &transferData(IClient *, void *, unsigned) = 0;
            virtual IClient &setOnDisconnect(std::function<void(const std::string &, unsigned id)> func) = 0;
            virtual IClient &Stop() = 0;
            virtual IClient &setBufferSize(unsigned) = 0;
            virtual ClientInfo &getInfos() = 0;
            virtual IClient &waitUntilDisconnect() = 0;
            virtual IClient &addPipeline(const std::string &name, const std::function<bool(IClient *, void *, unsigned)> &) = 0;
        };
    }
}
