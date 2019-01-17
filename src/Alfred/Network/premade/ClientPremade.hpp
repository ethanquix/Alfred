#pragma once

#include "Alfred/Logger/Logger.hpp"
#include "Alfred/Network/IClient.hpp"

namespace Alfred
{
    namespace Network
    {
        namespace Premade
        {
            void basic_string_displayer(PLACEHOLDER_TRANSFER_DATA_CALLBACK)
            {
                LOG.log("[CLIENT] Received from id: " + std::to_string(client->getInfos().id) + " ip: " + client->getInfos().ip + " port: " + std::to_string(client->getInfos().port) + " msg: " + std::string((char *)msg, size));
            }

        }
    }
}