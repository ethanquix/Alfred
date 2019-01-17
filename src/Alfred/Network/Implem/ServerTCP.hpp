#pragma once

#ifdef _WIN32

#include <Ws2tcpip.h>
#include <io.h>
#include <winsock2.h>
#include <windows.h>

#else
#include <sys/socket.h>
#include <cstring>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include "Alfred/Network/AServer.hpp"
#include "Alfred/Network/Implem/ClientTCP.hpp"
#include "Alfred/Network/exceptions/BindFailed.hpp"

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
                _info.in.sin_port = htons(_clientInfo.port);
                _info.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
                if (_info.fd == -1)
                    LOG.fatal("Socket creation error"); //TODO add perror
                if (bind(_info.fd, (const struct sockaddr *)(&_info.in), sizeof(_info.in)) == -1)
                    throw BindFailed(_clientInfo.ip, _clientInfo.port);
                if ((listen(_info.fd, _clientInfo.port)) == -1)
                    LOG.fatal("Listen failed");
            }

            void _accept()
            {
                struct sockaddr_in in;

                int fd = accept(_info.fd, (struct sockaddr *)&(in), &_sizeCurrentClient);
                _clients[fd] = _clientBuilder(in, fd);
                LOG.log("[SERVER] New client " + _clients[fd]->getInfos().ip + " port: " +
                        std::to_string(_clients[fd]->getInfos().port));
                _first_connect(this, fd);
                if (_asyncClient)
                    _clients[fd]->AsyncListen();
            }

            void select_check()
            {
                int index = -1;
                while (++index < FD_SETSIZE) {
                    if (FD_ISSET(index, &_rfds)) {
                        if (index == _info.fd) {
                            //New client
                            _accept();
                        } else {
                            _clients[index]->onNewMessage();
                        }
                    }
                }
            }

          public:

            ServerTCP() :
                AServer()
            {
                _bind();
            }

            explicit ServerTCP(unsigned port) :
                AServer(port)
            {
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