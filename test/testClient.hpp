#pragma once

#include <Network/Implem/ClientTCP.hpp>

class testClient : public Alfred::Network::ClientTCP
{
  public:
    testClient();

  protected:
    Alfred::Network::IClient &onReceived() override;

};

