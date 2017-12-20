#pragma once

#include <AlfredBase/Network/Implem/UDP.hpp>

class testClientUDP : public Alfred::Network::UDP
{
  public:
    testClientUDP() : UDP() {
    }
};
