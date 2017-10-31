#pragma once

#include <Logger/Logger.hpp>
#include "IServer.hpp"

namespace Alfred
{
    namespace Network
    {
        class AServer : public IServer
        {
          protected:
            unsigned _port;
            bool _isBind;
            bool _stop;

            Async::AsyncUnorderedMap<int, IClient *> _clients;
            std::function<void(IServer *, int clientFD)> _first_connect = [](IServer *, int clientFD) {};
            std::function<void(IServer *, int clientFD, const char *)> _on_received = [](IServer *, int clientFD, const char *) {};
            std::function<void(IServer *, int clientFD)> _on_disconnect = [](IServer *, int clientFD) {};
            std::function<IClient *(struct sockaddr_in in, unsigned fd)> _clientBuilder;

          public:
            AServer()
            {
                _port = DEFAULT_PORT;
                _isBind = false;
                _stop = false;
            }

            explicit AServer(unsigned port)
            {
                _port = port;
                _isBind = false;
                _stop = false;
            }

            Async::AsyncUnorderedMap<int, IClient *> &getClients() override
            {
                return _clients;
            }

            IClient &getClientInfo(int clientID) override
            {
                if (_clients.count(clientID) <= 0)
                    LOG.error("Error, client " + std::to_string(clientID) + " don't exist");
                return *_clients.at(clientID);
            }

            IServer &stop() override
            {
                _stop = true;
                return *this;
            }

            IServer &setClientBuilder(const std::function<IClient *(struct sockaddr_in in, unsigned fd)> &func) override
            {
                _clientBuilder = func;
                return *this;
            }

            IClient &operator[](int id) override
            {
                if (_clients.count(id) <= 0)
                    LOG.error("[SRRVER] Client doesnt exist: " + std::to_string(id));
                return *_clients[id];
            }

            IServer &onConnect(const std::function<void(IServer *, int)> &_func) override
            {
                _first_connect = _func;
                return *this;
            }

            IServer &onDisconnect(const std::function<void(IServer *, int)> &_func) override
            {
                _on_disconnect = _func;
                return *this;
            }

            IServer &clientDeleted(unsigned id) override
            {
                if (_clients.count(id) <= 0)
                    LOG.error("[SERVER] Client doesnt exist when deleting it: " + std::to_string(id));
                _clients.async_erase(id);
                return *this;
            }
        };
    }
}

