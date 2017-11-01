#pragma once

#include <Network/Implem/ClientTCP.hpp>

class testClient : public Alfred::Network::ClientTCP
{
  public:
    testClient() : ClientTCP() {

    };
  protected:
    Alfred::Network::IClient &setOnReceived() override;

};

