#pragma once

#include "AlfredBase/Network/Implem/ClientTCP.hpp"

class testServerClient : public Alfred::Network::ClientTCP
{
  public:
    Alfred::Network::IClient &setOnReceived() override
    {
        auto *out = new char[3];
        int ret = readUntil(out, 'A');
        if (ret != Alfred::Network::INDICATOR_DISCONNECT)
            transferData(this, out, ret);
//        int ret = readXChar(out, 2);
        return *this;
    }

    testServerClient(struct sockaddr_in in, unsigned fd) :
        ClientTCP(in, fd)
    {}
};

