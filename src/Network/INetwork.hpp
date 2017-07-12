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

    class INetwork
    {
    protected:
        ConnectionInfo info;

    public:
        explicit INetwork(int port);
        INetwork(int ip, int port);

        virtual INetwork &send(const std::string &msg) = 0;
        virtual INetwork &receive() = 0;
        //TODO CHANGE RECEIVE PROTO (return)
        //TODO IPACKETUTILS INTERFACE (with different possible implem) to parse to send and parse to receive (like send a vector of float and receive it
    };
}