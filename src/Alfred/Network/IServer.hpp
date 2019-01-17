#ifndef ALFRED_ISERVER_HPP
#define ALFRED_ISERVER_HPP

#include "Alfred/Async/AsyncUnorderedMap.hpp"
#include "Alfred/Network/IClient.hpp"
#include <unordered_map>
#include <unordered_map>
#include <functional>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <netinet/in.h>
#endif

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
            virtual IClient &getClientInfo(int clientID) = 0;
            virtual IServer &run() = 0;
            virtual IServer &asyncRun() = 0;
            virtual IServer &setAsyncClient(bool) = 0;
            virtual IServer &stop() = 0;
            virtual IServer &setClientBuilder(const std::function<IClient *(struct sockaddr_in in, unsigned fd)> &func) = 0;
            virtual IServer &clientDeleted(unsigned id) = 0;
            virtual IClient &operator[](int id) = 0;
        };
    }
}

#endif //ALFRED_ISERVER_HPP
