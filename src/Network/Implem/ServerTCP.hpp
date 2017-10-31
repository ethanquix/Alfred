/*
** UnixServer.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/UnixServer.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Sep 08 16:12:28 2017 Dimitri Wyzlic
** Last update Fri Sep 08 16:12:28 2017 Dimitri Wyzlic
*/

#pragma once

#include "AServer.hpp"
#include "ClientTCP.hpp"
#include <sys/socket.h>
#include <cstring>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <Network/exceptions/BindFailed.hpp>

namespace Alfred
{
    namespace Network
    {
        class ServerTCP : public AServer
        {
          private:
            InfoNetwork _info;
            fd_set _rfds;
            socklen_t _sizeCurrentClient = sizeof(struct sockaddr_in);
            std::thread *_asyncListenThread;

            void _bind()
            {
                _info.in.sin_addr.s_addr = INADDR_ANY;
                _info.in.sin_family = AF_INET;
                _info.in.sin_port = htons(_info.port);
                _info.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
                if (_info.fd == -1)
                    LOG.fatal("Socket creation error"); //TODO add perror
                if (bind(_info.fd, (const struct sockaddr *)(&_info.in), sizeof(_info.in)) == -1)
                    throw BindFailed(_info.ip, _info.port);
                if ((listen(_info.fd, _info.port)) == -1)
                    LOG.fatal("Listen failed");
            }

            void _accept()
            {
                struct sockaddr_in in;

                int fd = accept(_info.fd, (struct sockaddr *)&(in), &_sizeCurrentClient);
                _clients.async_at(fd) = _clientBuilder(in, fd);
                LOG.log("[SERVER] New client " + _clients.async_at(fd)->getInfos().ip + " port: " +
                        std::to_string(_clients.async_at(fd)->getInfos().port));
                _first_connect(this, fd);
//                _clients[fd]->AsyncListen();
            }

            void select_check()
            {
                int index = -1;
                while (++index < FD_SETSIZE) {
                    if (FD_ISSET(index, &_rfds)) {
                        if (index == _info.fd) {
                            LOG.log("hey");

                            //New client
                            _accept();
                        } else {
                            _clients.async_at(index)->onReceived();
                        //Returning client
                        //Balek le client s'en occupe comme un grand
//                            _currentClient.fd = index;
//                            tmp.in = _currentClient.in;
//                            tmp.fd = _currentClient.fd;
                        //Handle
//                            const char *msg = _receive();
//                            if (msg != nullptr)
//                                _on_received(this, tmp.fd, msg);
                        }
                    }
                }
            }

          public:

            ServerTCP() :
                AServer()
            {
                _info.port = _port; //TODO REMOVE THE BASE INFO STRUCT
                _bind();
            }

            explicit ServerTCP(unsigned port) :
                AServer(port)
            {
                _info.port = port;
                _bind();
            }

            virtual ~ServerTCP()
            {
                _stop = true;
                for (const auto &it: _clients)
                    it.second->Stop();
                if (_asyncListenThread != nullptr) {
                    _asyncListenThread->join();
                }
            }

            IServer &run() override
            {
                struct timeval tv = {};
                int retval;

                while (!_stop) {
                    tv.tv_usec = 0;
                    tv.tv_sec = 0;
                    FD_ZERO(&_rfds);
                    for (const auto &it : _clients)
                        FD_SET(it.first, &_rfds);
                    FD_SET(_info.fd, &_rfds);
                    if ((retval = select(_clients.size() + _info.fd + 2,
                                         &_rfds, NULL, NULL, &tv)) == -1 && !_stop)
                        LOG.fatal("Select failed"); //TODO CUSTOM EXCEPTION
                    else if (retval >= 0)
                        select_check();
                }
                return *this;
            }

            IServer &asyncRun() override
            {
                _asyncListenThread = new std::thread([this]() { this->run(); });
                return *this;
            }
        };
    }
}