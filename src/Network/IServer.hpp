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
#include "INetwork.hpp"

namespace Alfred
{
    class IServer : public INetwork
    {
    protected:
        std::unordered_map<int, ClientInfo> _clients;
        std::function<void(IServer *, const struct ConnectionInfo &)> _first_connect = nullptr;
        std::function<void(IServer *, const struct ConnectionInfo &, const char *)> _on_received = nullptr;
        std::function<void(IServer *, const struct ConnectionInfo &)> _on_disconnect = nullptr;

    public:
        IServer() : INetwork()
        {
        }

        explicit IServer(const size_t port) : INetwork(port)
        {
        }

        IServer(const std::string &ip, const size_t port) : INetwork(ip, port)
        {
        }

        virtual std::unordered_map<int, ClientInfo> &getClients()
        {
            return _clients;
        };

        virtual INetwork &onConnect(const std::function<void(IServer *, const struct ConnectionInfo &)> &_func)
        {
            _first_connect = _func;
            return *this;
        }

        virtual INetwork &
        onReceive(const std::function<void(IServer *, const struct ConnectionInfo &, const char *)> &_func)
        {
            _on_received = _func;
            return *this;
        }

        virtual INetwork &
        onDisconnect(const std::function<void(IServer *, const struct ConnectionInfo &)> &_func)
        {
            _on_disconnect = _func;
            return *this;
        }

        virtual INetwork &Send(const ConnectionInfo &to, const char *msg) = 0;

//        const int operator[](const size_t id)
//        {
//            if (_clients.find(id) == _clients.end())
//                return -1;
//            else
//                return _clients[id].fd;
//        }
        //TODO CHANGE SEND PROTO TO ONLY ACCEPT FD, THEN USE THIS TO BETTER ACCESS AND JUST server->Send(ID_CLIENT, "YOLO);
    };
}

#endif //ALFRED_ISERVER_HPP
