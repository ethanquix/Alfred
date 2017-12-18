#pragma once

#include <AlfredBase/Network/Implem/ClientUDP.hpp>

class testClientUDP : public Alfred::Network::ClientUDP
{
  public:
    testClientUDP() : ClientUDP() {
    }

    IClient &onNewMessage() override
    {
        std::cout << "J'ai recu un message" << std::endl;
        return *this;
    }
};
