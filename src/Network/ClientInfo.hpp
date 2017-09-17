/*
** ClientInfo.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/ClientInfo.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Mon Sep 18 00:57:13 2017 Dimitri Wyzlic
** Last update Mon Sep 18 00:57:13 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_CLIENTINFO_HPP
#define ALFRED_CLIENTINFO_HPP

#include "config.hpp"
#include "Random.hpp"
#include <netdb.h>

namespace Alfred
{
    struct ConnectionInfo
    {
        size_t port;
        std::string ip;
        int fd;
        struct sockaddr_in in;
        int id = Random::randint(0, INTMAX_MAX); //TODO UNIQUE ID GENERATOR
    };

    class ClientInfo
    {
    private:
        struct ConnectionInfo _info;

    public:
        ClientInfo() = default;

        explicit ClientInfo(const struct ConnectionInfo &info) :
            _info(info)
        {};

        const int getFD() const
        {
            return _info.fd;
        }

        const int getID() const
        {
            return _info.id;
        }
    };
}

#endif //ALFRED_CLIENTINFO_HPP
