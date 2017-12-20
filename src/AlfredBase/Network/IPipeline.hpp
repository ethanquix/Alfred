#pragma once

#include <string>
#include <AlfredBase/Logger/Logger.hpp>
#include "IClient.hpp"

namespace Alfred
{
    namespace Network
    {
        class IPipeline
        {
          public:
            virtual ~IPipeline() = default;
            virtual const std::string &getName() const = 0;

            virtual bool onFirstConnect(IClient *client)
            {
                LOG.fatal("[IPIPELINE] Not implemented");
            }

            virtual std::tuple<bool, IClient *, void *, unsigned> onReceiveMessage(IClient *client, void *msg, unsigned len)
            {
                LOG.fatal("[IPIPELINE] Not implemented");
            }

            virtual std::tuple<bool, IClient *, void *, unsigned> onSendMessage(IClient *client, void *msg, unsigned len)
            {
                LOG.fatal("[IPIPELINE] Not implemented");
            }

            virtual bool onDisconnect(IClient *client)
            {
                LOG.fatal("[IPIPELINE] Not implemented");
            }
        };
    }
}

