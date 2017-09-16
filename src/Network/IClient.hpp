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

#include <functional>
#include "INetwork.hpp"

namespace Alfred
{
    class IClient : public INetwork
    {
    protected:
        std::function<void(IClient *, const char *msg)> _onReceived;

    public:
        IClient() : INetwork()
        {
        }

        explicit IClient(const size_t port) : INetwork(port)
        {
        }

        IClient(const std::string &ip, const size_t port) : INetwork(ip, port)
        {
        }

        virtual IClient &Connect() = 0;
        virtual IClient &Connect(const std::string &ip, size_t port) = 0;

        virtual INetwork &send(const char *msg) = 0;

        virtual IClient &onReceived(const std::function<void(IClient *, const char *msg)> &func)
        {
            _onReceived = func;
            return *this;
        }
//Et la send qui est virtual oklm
    };
}

#endif //ALFRED_ICLIENT_HPP
