#pragma once

#include <Alfred/Network/Implem/UDP.hpp>

class testClientUDP : public Alfred::Network::UDP
{
  public:
    testClientUDP() : UDP() {
    }
};
