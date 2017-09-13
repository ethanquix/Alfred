/*
** UnixServer.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/UnixServer.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Sep 08 16:12:28 2017 Dimitri Wyzlic
** Last update Fri Sep 08 16:12:28 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_UNIXSERVER_HPP
#define ALFRED_UNIXSERVER_HPP

#include <netdb.h>
#include <unistd.h>
#include "IServer.hpp"

namespace Alfred
{
    class UnixServerTCP : public IServer
    {
    private:
        fd_set rfds;
        size_t client_fd;
        struct sockaddr_in client_in;
        socklen_t size = sizeof(client_in);

        void _bind()
        {
            _info.in.sin_addr.s_addr = INADDR_ANY;
            _info.in.sin_family = AF_INET;
            _info.in.sin_port = htons(_info.port);
            _info.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
            if (_info.fd == -1)
                LOG.fatal("Socket creation error"); //TODO add perror
            if (bind(_info.fd, (const struct sockaddr *)(&_info.in), sizeof(_info.in)) == -1)
                LOG.fatal("Bind failed");
            if ((listen(_info.fd, _info.port)) == -1)
                LOG.fatal("Listen failed");
        }

        void _accept()
        {
            client_fd = accept(_info.fd, (struct sockaddr *)&(client_in),
                               &size);
        }

        char *_receive()
        {
            char *buff = new char[1024 * sizeof(char)];
            ssize_t index;

            if ((index = read(client_fd, buff, 1024)) <= 0) {
                if (index < 0)
                    LOG.error("Failed to read");
                close(client_fd);
                printf("Client %zu Disconnected\n", client_fd);
                _clients.erase(client_fd);
                return (nullptr);
            }
            buff[index] = '\0';
            LOG.debug(std::to_string(client_fd) + " " + std::string(buff));
            return (buff);
        }

        void select_check()
        {
            struct ConnectionInfo tmp;

            int index = -1;
            while (++index < FD_SETSIZE) {
                if (FD_ISSET(index, &rfds)) {
                    if (index == _info.fd) {
                        //New client
                        _accept();
                        tmp.in = client_in;
                        tmp.fd = client_fd;
                        this->_clients[client_fd] = tmp;
                        printf("Client %zu Connected\n", client_fd);
                        _first_connect(this, tmp);
                    } else {
                        //Returning client
                        client_fd = index;
                        tmp.in = client_in;
                        tmp.fd = client_fd;
                        //Handle
                        _on_received(this, tmp);
                    }
                }
            }
        }

    public:
        UnixServerTCP() :
            IServer()
        {
            _mode = TCP;
            _bind();
        }

        explicit UnixServerTCP(const size_t port) :
            IServer(port)
        {
            _mode = TCP;
            _bind();
        }

        UnixServerTCP(const std::string &ip, const size_t port) :
            IServer(ip, port)
        {
            _mode = TCP;
            _bind();
        }

        INetwork &send(const ConnectionInfo &to, const char *msg) override
        {
            dprintf(to.fd, "%s", msg);
            return *this;
        }

        INetwork &receive() override
        {
            _receive();
            //TODO RETURN CHAR *
            return *this;
        }

        INetwork &run() override
        {
            struct timeval tv = {};
            int retval;

            //TODO loop here infinite

            while (!_stop) {
                tv.tv_usec = 0;
                tv.tv_sec = 0;
                FD_ZERO(&rfds);
                for (const auto &it : _clients)
                    FD_SET(it.second.fd, &rfds);
                FD_SET(_info.fd, &rfds);
                if ((retval = select(_clients.size() + _info.fd + 2,
                                     &rfds, NULL, NULL, &tv)) == -1 && !_stop/* TODO && NOT SIGNAL */)
                    LOG.fatal("Select failed"); //TODO CUSTOM EXCEPTION
                else if (retval >= 0)
                    select_check();
            }
            //TODO END LOOP
            return *this;
        }
    };
}

#endif //ALFRED_UNIXSERVER_HPP
