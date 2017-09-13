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
        virtual IClient &connect() = 0;
//        virtual IClient &connectTo(const std::string &ip, size_t port) = 0; TODO
        virtual void listen() = 0;

        virtual IClient &onReceived(const std::function<void(IClient *, const char *msg)> &func)
        {
            _onReceived = func;
            return *this;
        }
//Et la send qui est virtual oklm
    };
}

#endif //ALFRED_ICLIENT_HPP
