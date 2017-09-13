#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

#define DEFAULT_PORT 8000
#define DEFAULT_IP "127.0.0.1"

namespace Alfred
{
    struct ConnectionInfo
    {
        size_t port;
        std::string ip;
        int fd;
        struct sockaddr_in in;
    };

    enum ConnectionMode
    {
        TCP = 0,
        UDP
    };

    class INetwork
    {
    protected:
        ConnectionInfo _info = {};
        enum ConnectionMode _mode;

    public:
        INetwork()
        {
            _info.port = DEFAULT_PORT;
            _info.ip = DEFAULT_IP;
        };

        explicit INetwork(const size_t port)
        {
            _info.ip = DEFAULT_IP;
            _info.port = port;
        };

        INetwork(const std::string &ip, const size_t port)
        {
            _info.ip = ip;
            _info.port = port;
        };

        virtual INetwork &send(const ConnectionInfo &to, const char *msg) = 0;
        virtual INetwork &receive() = 0;
        //TODO CHANGE RECEIVE PROTO (return)
        //TO_[DONE] IPACKETUTILS INTERFACE (with different possible implem) to parse to send and parse to receive (like send a vector of float and receive it
    };
}