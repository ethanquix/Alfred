/*
** ClientTCP.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/ClientTCP.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Sep 13 16:13:32 2017 Dimitri Wyzlic
** Last update Wed Sep 13 16:13:32 2017 Dimitri Wyzlic
*/

#pragma once

#include <netinet/in.h>
#include <netdb.h>
#include <Logger/Logger.hpp>
#include <unistd.h>
#include <Network/AClient.hpp>
#include <Network/exceptions/BindFailed.hpp>
#include <cstring>

namespace Alfred
{
    namespace Network
    {
        struct InfoNetwork
        {
            std::string ip;
            unsigned port;
            int fd;
            struct sockaddr_in in;
        };

        class ClientTCP : public AClient
        {
          private:
            fd_set _rdfs = {};
            struct InfoNetwork _info;
            std::thread *_asyncListenThread;

          private:
            void _bind()
            {
                _info.in.sin_addr.s_addr = INADDR_ANY;
                _info.in.sin_family = AF_INET;
                _info.in.sin_port = htons(_info.port);
                _info.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
                if (_info.fd == -1)
                    LOG.fatal("Socket creation error");
                if (connect(_info.fd, (const struct sockaddr *)(&_info.in), sizeof(_info.in)) == -1)
                    throw BindFailed(_info.ip, _info.port);
            }

            void deplaceChar(char **from, unsigned start, unsigned end)
            {
                unsigned i = 0;
                while (start < end)
                {
                    (*from)[i] = (*from)[start];
                    i += 1;
                    start += 1;
                }
            }

          public:

            ClientTCP() :
                AClient()
            {
                _asyncListenThread = nullptr;
            };

            IClient &Connect() override
            {
                AClient::Connect();
                _info.ip = _ip;
                _info.port = _port;
                _bind();
                _isBind = true;
                return *this;
            }

            IClient &Connect(unsigned port) override
            {
                AClient::Connect(port);
                _info.ip = _ip;
                _info.port = _port;
                _bind();
                _isBind = true;
                return *this;
            }

            IClient &Connect(const std::string &ip, const unsigned port) override
            {
                AClient::Connect(ip, port);
                _info.ip = ip;
                _info.port = port;
                _bind();
                _isBind = true;
                return *this;
            }

            int readXChar(void *buf, unsigned size)
            {
                int ret = read(_info.fd, buf, size);
                if (ret <= 0)
                    _on_disconnect("Read failed");
                return ret;
            }

            int readUntil(void *buf, char target)
            {
                static char *savedBuffer = new char[_bufferSize];
                static int savedBytesRead = 0;
                static unsigned curMaxSize = 0;

                char *tmp = new char[_bufferSize];
                int bytesRead;
                unsigned i = 0;

                while (true)
                {
                    while (i < curMaxSize)
                    {
                        if (savedBuffer[i] == target)
                        {
                            if (std::realloc(buf, (i + 1) * sizeof(char)) == NULL)
                                LOG.fatal("Realloc failed");
                            std::strncpy((char *)buf, savedBuffer, i + 1);
                            deplaceChar(&savedBuffer, i + 1, curMaxSize);
                            curMaxSize -= i + 1;
                            return i;
                        }
                        i += 1;
                    }

                    bytesRead = read(_info.fd, tmp, _bufferSize);
                    if (bytesRead <= 0)
                        _on_disconnect("Error during read at read until");
                    if (std::realloc(savedBuffer, (curMaxSize + bytesRead) * sizeof(char)) == NULL)
                        LOG.fatal("Realloc failed");
                    std::strncpy(&(savedBuffer[curMaxSize]), tmp, bytesRead);
                    curMaxSize += bytesRead;
                }
            }

            IClient &Listen() override
            {
                int retval;

                if (!_isBind)
                    LOG.fatal("You need to call Connect before calling Listen");
                while (!_stop) {
                    FD_ZERO(&_rdfs);
                    FD_SET(_info.fd, &_rdfs);
                    retval = select(_info.fd + 1, &_rdfs, NULL, NULL, NULL);
                    if (retval == -1) {
                        _on_disconnect("Select failed");
                        _stop = true;
                    } else if (retval >= 0)
                        onReceived();
                }
                close(_info.fd);
                return *this;
            }

            IClient &Send(void *msg, unsigned size) override
            {
                write(_info.fd, msg, size);
                return *this;
            }

            IClient &AsyncListen() override
            {
                _asyncListenThread = new std::thread([this]() { this->Listen(); });
                return *this;
            }

            ~ClientTCP() override
            {
                _stop = true;
                if (_asyncListenThread != nullptr) {
                    _asyncListenThread->join();
                }
            }
        };
    }
}