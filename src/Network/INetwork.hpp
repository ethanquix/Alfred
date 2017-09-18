#pragma once

#include "Logger.hpp"
#include "ClientInfo.hpp"
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

#define DEFAULT_PORT 8000
#define DEFAULT_IP "127.0.0.1"

namespace Alfred
{
    class BindFailed : public std::exception
    {
        std::string msg;
    public:
        BindFailed(const std::string &ip, int port) :
            msg(std::string("Failed to bind to ip: ") + ip + " and port " + std::to_string(port))
        {}

        virtual const char *what() const throw()
        { return msg.c_str(); }
    };

    struct PacketHeader //TODO CHANGE THAT BY ONE STRUCT PER CLIENT AND SEND STRUCT AT START TO SAY IF YES OR NOT LENGTH OR END DELIMITER OR FIXED SIZE
    {
        int length;
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
        enum ConnectionMode _mode = TCP;
        bool _stop = false;
        bool _isBind = false;
        int _packetSize = 1024;
        int _lengthIndicatorSize = 4;

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

        virtual void stop()
        {
            _stop = true;
        }

        INetwork &setPacketSize(int packetSize)
        {
            _packetSize = packetSize;
            return *this;
        }

        INetwork &setLengthIndicatorSize(int lengthIndicatorSize)
        {
            _lengthIndicatorSize = lengthIndicatorSize;
            return *this;
        }

        //TO_[DONE] IPACKETUTILS INTERFACE (with different possible implem) to parse to send and parse to receive (like send a vector of float and receive it


        //TODO Multithreading
        //TODO Hostname resolution
        //TODO FUNCTION ON DISCONNECT
        //TODO CHECK IF SERVER AND CLIENT WELL CONNECTED BEFORE SENDING MSG
        //TODO ADD ON_DISCONNECT CLIENT
        //TODO ADD DEFAULT FUNCTION FOR CLIENT AND SERVER
        //TODO CHANGE CONNECT BEHAVIOR (Like not _bind in constructor but in connect)
        //TODO CHANGE CLIENT WHICH CAN NOT SEND ANY MSG
    };
}