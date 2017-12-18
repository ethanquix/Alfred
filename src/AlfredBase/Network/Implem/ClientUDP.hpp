#pragma once

#include <cstring>

#include "AlfredBase/Logger/Logger.hpp"
#include "AlfredBase/Network/exceptions/BindFailed.hpp"
#include "AlfredBase/Network/AClient.hpp"
#include "AlfredBase/Random/Random.hpp"
#include "ClientTCP.hpp"

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

namespace Alfred
{
    namespace Network
    {
        class ClientUDP : public AClient
        {
          private:
            struct InfoNetwork _info;
          private:
            void _bind()
            {
                _info.in.sin_addr.s_addr = inet_addr(_clientInfo.ip.c_str());
                if (_info.in.sin_addr.s_addr == (u_long)INADDR_NONE)
                    LOG.fatal("Bad ip");
                _info.in.sin_family = AF_INET;
                _info.in.sin_port = htons(_clientInfo.port);
                _info.fd = socket(AF_INET, SOCK_DGRAM, 0);
                _clientInfo.id = _info.fd;
                if (_info.fd == -1)
                    LOG.fatal("Socket creation error");
            }

            IClient &prepare()
            {
                _bind();
                _isBind = true;
                return *this;
            }

          public:
            IClient &Send(void *msg, unsigned size) override
            {
                if (sendto(_info.fd, msg, size, 0, (sockaddr *)&_info.in, sizeof(_info.in)) < 0) {
                    perror("sendto()");
                    exit(errno);
                }
                return *this;
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

            IClient &Listen() override
            {
                return *this;
            }

            IClient &AsyncListen() override
            {
                return *this;
            }

            ClientInfo &getInfos() override
            {
                return _clientInfo;
            }
        };
    }
}

