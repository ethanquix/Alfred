#pragma once

#include <Network/Implem/ClientTCP.hpp>

class testServerClient : public Alfred::Network::ClientTCP
{
  public:
    Alfred::Network::IClient &onReceived() override
    {
        auto *out = new char[3];
//    LOG.warning(std::to_string(readXChar(out, 2)));
//    out[3]  = '\0';
        int ret = readUntil(out, 'A');
        transferData(this, out, ret);
        return *this;
    }

    testServerClient(struct sockaddr_in in, unsigned fd) :
        ClientTCP(in, fd)
    {}
};

