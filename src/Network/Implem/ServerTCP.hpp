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

#include <cstring>
#include <sys/ioctl.h>
#include "IServer.hpp"

namespace Alfred
{
    class ServerTCP : public IServer
    {
    private:
        struct ConnectionInfo _currentClient;
        fd_set _rfds;
        socklen_t _sizeCurrentClient = sizeof(_currentClient.in);

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
            _currentClient.fd = accept(_info.fd, (struct sockaddr *)&(_currentClient.in),
                                       &_sizeCurrentClient);
        }

        const char *_receive()
        {
            ssize_t index;
            std::stringstream out;
            char *buff = new char[4096 * sizeof(char)];
            std::string x;
            int to_receive = 1;
            int received = 0;

            //TODO SEND FIRST RECEIVE AND THEN TO RECEIVE BLABLA
            //TODO SAME FOR CLIENT
            while (!_stop && received < to_receive) {
                bzero(buff, 4096);
                if ((index = read(_currentClient.fd, buff, 4096)) <= 0) {
                    if (index < 0)
                        LOG.error("Failed to read");
                    close(_currentClient.fd);
                    printf("Client %d Disconnected\n", _currentClient.fd);
                    _on_disconnect(this, _currentClient);
                    _clients.erase(_currentClient.fd);
                    return (nullptr);
                }
                std::cout << buff[index - 1] << std::endl;
                if (buff[index - 1] == _endChar) {
                    buff[index - 1] = '\0';
                    out << buff;
                    out >> x;
                    out.clear();
                    LOG.error("ON SE TIRE " + x);
                    return x.c_str(); //TODO MAYBE JUST STRING OR REALLOC DUDE
                }
                buff[index] = '\0'; //TODO ?
                LOG.error("CUR BUF: " + std::string(buff));
                out << buff;
            }
        }

        void select_check()
        {
            struct ConnectionInfo tmp;

            int index = -1;
            while (++index < FD_SETSIZE) {
                if (FD_ISSET(index, &_rfds)) {
                    if (index == _info.fd) {
                        //New client
                        _accept();
                        tmp.in = _currentClient.in;
                        tmp.fd = _currentClient.fd;
                        this->_clients[_currentClient.fd] = tmp;
                        printf("Client %d Connected\n", _currentClient.fd);
                        _first_connect(this, tmp);
                    } else {
                        //Returning client
                        _currentClient.fd = index;
                        tmp.in = _currentClient.in;
                        tmp.fd = _currentClient.fd;
                        //Handle
                        _on_received(this, tmp, _receive());
                    }
                }
            }
        }

    public:

        ServerTCP() :
            IServer()
        {
            _bind();
        }

        explicit ServerTCP(const size_t port) :
            IServer(port)
        {
            _bind();
        }

        ServerTCP(const std::string &ip, const size_t port) :
            IServer(ip, port)
        {
            _bind();
        }

        INetwork &send(const ConnectionInfo &to, const char *msg) override
        {
            dprintf(to.fd, "%s", msg);
            return *this;
        }

        INetwork &run() override
        {
            struct timeval tv = {};
            int retval;

            while (!_stop) {
                tv.tv_usec = 0;
                tv.tv_sec = 0;
                FD_ZERO(&_rfds);
                for (const auto &it : _clients)
                    FD_SET(it.second.fd, &_rfds);
                FD_SET(_info.fd, &_rfds);
                if ((retval = select(_clients.size() + _info.fd + 2,
                                     &_rfds, NULL, NULL, &tv)) == -1 && !_stop)
                    LOG.fatal("Select failed"); //TODO CUSTOM EXCEPTION
                else if (retval >= 0)
                    select_check();
            }
            return *this;
        }
    };
}

#endif //ALFRED_UNIXSERVER_HPP
