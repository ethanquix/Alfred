/*
** ClientTCP.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/ClientTCP.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Sep 13 16:13:32 2017 Dimitri Wyzlic
** Last update Wed Sep 13 16:13:32 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_CLIENTTCP_HPP
#define ALFRED_CLIENTTCP_HPP

#include "Logger.hpp"
#include "IClient.hpp"

namespace Alfred
{
    class ClientTCP : public IClient
    {
    private:
        fd_set rdfs = {};

        void _bind()
        {
            _info.in.sin_addr.s_addr = INADDR_ANY;
            _info.in.sin_family = AF_INET;
            _info.in.sin_port = htons(_info.port);
            _info.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
            if (_info.fd == -1)
                LOG.fatal("Socket creation error"); //TODO add perror
            if (connect(_info.fd, (const struct sockaddr *)(&_info.in), sizeof(_info.in)) == -1)
                throw BindFailed(_info.ip, _info.port);
        }

        const char *_receive()
        {
            char *buff = new char[_packetSize * sizeof(char)];
            ssize_t index;

            if ((index = read(_info.fd, buff, _packetSize)) <= 0) {
                if (index < 0)
                    LOG.error("Failed to read");
                close(_info.fd);
                printf("Server %d Disconnected\n", _info.fd);
                stop();
                _on_disconnect();
                return (nullptr);
            }
            buff[index] = '\0';
            LOG.debug(std::to_string(_info.fd) + " " + std::string(buff));
            return (buff);
        }

        void select_check()
        {
            const char *msg = _receive();
            if (msg)
                _onReceived(this, msg);
        }

    public:
        ClientTCP() : IClient()
        {}

        explicit ClientTCP(const size_t port) : IClient(port)
        {}

        ClientTCP(const std::string &ip, const size_t port) : IClient(ip, port)
        {}

        IClient &Connect() override
        {
            _isBind = false;
            _bind();
            _isBind = true;
            return *this;
        }

        IClient &Connect(const std::string &ip, const size_t port) override
        {
            _isBind = false;
            _info.ip = ip;
            _info.port = port;
            _bind();
            _isBind = true;
            return *this;
        }

        IClient &Listen() override
        {
            int retval;

            if (!_isBind)
                LOG.fatal("You need to call Connect before call Listen");
            while (!_stop) {
                FD_ZERO(&rdfs);
                FD_SET(_info.fd, &rdfs);
                retval = select(_info.fd + 1, &rdfs, NULL, NULL, NULL);
                if (retval == -1)
                    LOG.fatal("Select failed"); //TODO CUSTOM EXCEPTION
                else if (retval >= 0)
                    select_check();
            }
            close(_info.fd);
            return *this;
        }

        //TODO CHANGE RECEIVE METHOD BY LENGTH OR FIXED LENGTH
        IClient &Send(const char *msg) override //TODO CHANGE PROTO BY VOID * AND SIZE_T LENGTH
        {
            struct PacketHeader header;

            std::string tmp(msg);
            header.length = tmp.size();
            write(_info.fd, &header, sizeof(struct PacketHeader));
            dprintf(_info.fd, "%s", msg);
            return *this;
        }
    };
}

#endif //ALFRED_CLIENTTCP_HPP
