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

        void _bind()
        {
            _info.in.sin_addr.s_addr = INADDR_ANY;
            _info.in.sin_family = AF_INET;
            _info.in.sin_port = htons(_info.port);
            _info.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
            if (_info.fd == -1)
                LOG.fatal("Socket creation error"); //TODO add perror
            if (connect(_info.fd, (const struct sockaddr *)(&_info.in), sizeof(_info.in)) == -1)
                LOG.fatal("Bind failed");
            if ((listen(_info.fd, _info.port)) == -1)
                LOG.fatal("Listen failed");
        }

    public:
        ClientTCP() : IClient()
        {
            _bind();
        }

        explicit ClientTCP(const size_t port) : IClient(port)
        {
            _bind();
        }

        ClientTCP(const std::string &ip, const size_t port) : IClient(ip, port)
        {
            _bind();
        }

        IClient &Connect() override
        {
            _bind();
            return *this;
        }

        IClient &Connect(const std::string &ip, const size_t port) override
        {
            _info.ip = ip;
            _info.port = port;
            _bind();
            return *this;
        }

        INetwork &run() override
        {
            //TODO LOOP ETC
            return *this;
        }

        INetwork &send(const char *msg) override
        {
            dprintf(_info.fd, "%s", msg);
            return *this;
        }

        const char *_receive()
        {
            char *buff = new char[1024 * sizeof(char)];
            ssize_t index;

            if ((index = read(_info.fd, buff, 1024)) <= 0) {
                if (index < 0)
                    LOG.error("Failed to read");
                close(_info.fd);
                printf("Server %zu Disconnected\n", _info.fd);
                return (nullptr);
            }
            buff[index] = '\0';
            LOG.debug(std::to_string(_info.fd) + " " + std::string(buff));
            return (buff);
        }

        IClient &onReceived(const std::function<void(IClient *, const char *)> &func) override
        {
            _onReceived(this, _receive());
        }
    };
}

#endif //ALFRED_CLIENTTCP_HPP
