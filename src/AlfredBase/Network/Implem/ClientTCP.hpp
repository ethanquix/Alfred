#pragma once

#include "AlfredBase/Logger/Logger.hpp"
#include "AlfredBase/Network/exceptions/BindFailed.hpp"
#include "AlfredBase/Network/AClient.hpp"
#include "AlfredBase/Random/Random.hpp"

#ifdef _WIN32

#include <Ws2tcpip.h>
#include <io.h>
#include <winsock2.h>
#include <windows.h>

#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include <cstring>

#pragma warning(disable:4244)

namespace Alfred
{
    namespace Network
    {
        struct InfoNetwork
        {
#ifdef _WIN32
            SOCKET fd;
#else
            int fd;

#endif
            struct sockaddr_in in;
        };

        class ClientTCP : public AClient
        {
          private:
            fd_set _rdfs = {};
            struct InfoNetwork _info;
            std::thread *_asyncListenThread;

            char *_savedBuffer = new char[_bufferSize];
            int _savedBytesRead = 0;
            unsigned _curMaxSize = 0;

          private:
            void _bind()
            {
                _info.in.sin_addr.s_addr = inet_addr(_clientInfo.ip.c_str());
                if (_info.in.sin_addr.s_addr == (u_long)INADDR_NONE)
                    LOG.fatal("Bad ip");
                _info.in.sin_family = AF_INET;
                _info.in.sin_port = htons(_clientInfo.port);
                _info.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
                _clientInfo.id = _info.fd;
                if (_info.fd == -1)
                    LOG.fatal("Socket creation error");
                if (connect(_info.fd, (const struct sockaddr *)(&_info.in), sizeof(_info.in)) == -1)
                    throw BindFailed(_clientInfo.ip, _clientInfo.port);
            }

            void deplaceChar(char **from, unsigned start, unsigned end)
            {
                unsigned i = 0;
                while (start < end) {
                    (*from)[i] = (*from)[start];
                    i += 1;
                    start += 1;
                }
            }

            IClient &prepare()
            {
                _bind();
                _isBind = true;
                return *this;
            }

          public:

            ClientTCP() :
                AClient()
            {
                _asyncListenThread = nullptr;
            };

            ClientTCP(struct sockaddr_in in, unsigned fd) :
                AClient()
            {
                _asyncListenThread = nullptr;
                _info.in = in;
                _info.fd = fd;

                _isBind = true;

                char ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &in.sin_addr, ip, INET_ADDRSTRLEN);
                _clientInfo.ip = std::string(ip);
                _clientInfo.port = in.sin_port;
                _clientInfo.id = fd;
            }

            IClient &Connect() override
            {
                AClient::Connect();
                return prepare();
            }

            IClient &Connect(unsigned port) override
            {
                AClient::Connect(port);
                return prepare();
            }

            IClient &Connect(const std::string &ip, const unsigned port) override
            {
                AClient::Connect(ip, port);
                return prepare();
            }

            int readXChar(void *buf, unsigned size)
            {
                int ret = read(_info.fd, buf, size);
                if (ret <= 0) {
                    _on_disconnect("Read failed", _info.fd);
                    _stop = true;
                    return INDICATOR_DISCONNECT;
                }
                return ret;
            }

            int readUntil(void *buf, char target)
            {
                char *tmp = new char[_bufferSize];
                int bytesRead;
                unsigned i;

                while (true) {
                    i = 0;
                    while (i < _curMaxSize) {
                        if (_savedBuffer[i] == target) {
                            if (std::realloc(buf, (i + 1) * sizeof(char)) == NULL)
                                LOG.fatal("Realloc failed");
                            std::strncpy((char *)buf, _savedBuffer, i + 1);
                            deplaceChar(&_savedBuffer, i + 1, _curMaxSize);
                            _curMaxSize -= i + 1;
                            return i;
                        }
                        i += 1;
                    }

                    bytesRead = read(_info.fd, tmp, _bufferSize);
                    if (bytesRead <= 0) {
                        _on_disconnect("Error during read at read until", _info.fd);
                        _stop = true;
                        return INDICATOR_DISCONNECT;
                    }
                    if (std::realloc(_savedBuffer, (_curMaxSize + bytesRead) * sizeof(char)) == NULL)
                        LOG.fatal("Realloc failed");
                    std::strncpy(&(_savedBuffer[_curMaxSize]), tmp, bytesRead);
                    _curMaxSize += bytesRead;
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
                        _on_disconnect("Select failed", _info.fd);
                        _stop = true;
                    } else if (retval >= 0)
                        onNewMessage();
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

            ClientInfo &getInfos() override
            {
                return _clientInfo;
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