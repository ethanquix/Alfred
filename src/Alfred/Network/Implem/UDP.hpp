#pragma once

#include <cstring>

#include "Alfred/Logger/Logger.hpp"
#include "Alfred/Network/exceptions/BindFailed.hpp"
#include "Alfred/Network/AClient.hpp"
#include "Alfred/Random/Random.hpp"
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
        class UDP : public AClient
        {
          private:
            struct InfoNetwork _info;
            ClientInfo _udpInfo;
            std::unordered_map<std::string, struct sockaddr_in> _clients;

          private:
            void _bind()
            {
                _info.in.sin_addr.s_addr = inet_addr(_clientInfo.ip.c_str());
                if (_info.in.sin_addr.s_addr == (u_long)INADDR_NONE)
                    LOG.fatal("Bad ip");
                _info.in.sin_family = AF_INET;
                _info.in.sin_port = htons(_clientInfo.port);
                _info.fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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

            std::string getIdentifier(char *msg, unsigned len)
            {
                if (len < IDENTIFIER_SIZE)
                {
                    LOG.error("[UDP] Msg too short while getting identifier");
                    return "";
                }

                std::string out = msg;

                return out.substr(0, IDENTIFIER_SIZE);
            }

          public:
            IClient &Send(void *msg, unsigned size) override
            {
                LOG.error("Not implemented in UDP use UDP::SendTo instead");
//                if (sendto(_info.fd, msg, size, 0, (sockaddr *)&_info.in, sizeof(_info.in)) < 0) {
//                    perror("sendto()");
//                    exit(errno);
//                }
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
                if (!_isBind)
                    LOG.fatal("You need to call Connect before calling Listen");

                struct sockaddr *udpaddrfrom = new struct sockaddr;

                if (bind(_info.fd, (struct sockaddr *) &_info.in, sizeof(_info.in))) {
                    perror("binding datagram socket");
                    exit(1);
                }

                unsigned int bytes;
                char message[BUFFER_SIZE];

                socklen_t fromlen = sizeof(*udpaddrfrom);

                bool pipelinesBool = true;

                while (!_stop)
                {
                    while ((bytes = recvfrom(_info.fd, message, BUFFER_SIZE, 0, udpaddrfrom, &fromlen)) != 0)
                    {
                        message[bytes] = '\0';

                        struct sockaddr_in *tmp = (struct sockaddr_in *) udpaddrfrom;
                        std::string ip = inet_ntoa(tmp->sin_addr);
                        int port = ntohs(tmp->sin_port);

                        _udpInfo.ip = ip;
                        _udpInfo.port = port;

                        for (const auto &it : _pipelines)
                            if (!it.second(this, message, bytes)) {
                                pipelinesBool = false;
                                break;
                            }

                        if (pipelinesBool)
                            transferData(this, message, bytes);

                        pipelinesBool = true;
                    }
                }
                return *this;
            }

            IClient &AsyncListen() override
            {
                LOG.fatal("NOT IMPLEMENTED");
                return *this;
            }

            /**
             * @brief Get infos about the current received message
             * @return
             */
            ClientInfo &getInfos() override
            {
                return _udpInfo;
            }

            IClient &onNewMessage() override
            {
                LOG.fatal("NOT USED BY UDP");
                return *this;
            }

            IClient &SendTo(const std::string &ip, int port, void *msg, unsigned size) override
            {
                InfoNetwork tmp;

                tmp.in.sin_addr.s_addr = inet_addr(ip.c_str());
                if (tmp.in.sin_addr.s_addr == (u_long)INADDR_NONE)
                    LOG.fatal("Bad ip");
                tmp.in.sin_family = AF_INET;
                tmp.in.sin_port = htons(port);
                tmp.fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                if (tmp.fd == -1)
                    LOG.fatal("Socket creation error");

                if (sendto(tmp.fd, msg, size, 0, (sockaddr *)&tmp.in, sizeof(tmp.in)) < 0) {
                    perror("sendto()");
                    exit(errno);
                }
                close(tmp.fd);
                return *this;
            }
        };
    }
}

