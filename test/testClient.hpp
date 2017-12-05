#pragma once

#include <AlfredBase/Network/Implem/ClientTCP.hpp>

class testClient : public Alfred::Network::ClientTCP
{
  public:
    testClient() : ClientTCP() {
    };

  protected:
    Alfred::Network::IClient &onNewMessage() override;
};

