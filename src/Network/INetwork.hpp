#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

namespace Alfred
{
    struct ConnectionInfo
    {
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
        ConnectionInfo info;

    public:
        INetwork() = delete;
        explicit INetwork(int port) = delete;
        INetwork(int ip, int port) = delete;

        virtual INetwork &send(const ConnectionMode &mode, const char *msg) = 0;
        virtual INetwork &receive() = 0;
        //TODO CHANGE RECEIVE PROTO (return)
        //TO_[DONE] IPACKETUTILS INTERFACE (with different possible implem) to parse to send and parse to receive (like send a vector of float and receive it
    };
}