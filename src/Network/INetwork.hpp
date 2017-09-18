#pragma once

#include "Logger.hpp"
#include "ClientInfo.hpp"
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>


//TODO
//IDEE: En gros, CLIENT:
// 1 thread pour recevoir et ducoup send se fait sur le principal
// POUR SERVER
// Un thread pour send (sendqueue)

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
//
//    struct PacketHeader //TODO CHANGE THAT BY ONE STRUCT PER CLIENT AND SEND STRUCT AT START TO SAY IF YES OR NOT LENGTH OR END DELIMITER OR FIXED SIZE
//    {
//        int length;
//    };
//
//    std::ostringstream &operator<<(std::ostringstream &os, struct PacketHeader &h)
//    {
//        os << h.length;
//        return os;
//    }
//
//    std::string &operator>>(std::string &src, struct PacketHeader &h)
//    {
//        std::istringstream iss(src);
//
//        iss >> h.length;
//        return src;
//    }

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
        size_t _lengthIndicatorSize = sizeof(int);
        bool _threaded; //TODO

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

        //TODO Multithreading
        //TODO Hostname resolution
        //TODO CHANGE CLIENT WHICH CAN NOT SEND ANY MSG [REFER MULTITHREADING]
    };
}