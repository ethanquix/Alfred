#pragma once

#include "Alfred/Network/IClient.hpp"
#include "Alfred/Logger/Logger.hpp"
#include <thread>
#include <string>

namespace Alfred
{
    namespace Network
    {
        class AClient : public IClient
        {
          protected:
            ClientInfo _clientInfo;
            bool _isBind;
            bool _stop;
            unsigned _bufferSize;

            std::vector<std::pair<std::string, std::function<bool(IClient *, void *, unsigned)>>> _pipelines;

            std::function<void(IClient *, void *, unsigned)> _onReceived = [](IClient *, void *, unsigned) { LOG.fatal("You need to set a transferDataCallback function"); };
            std::function<void(const std::string &, unsigned)> _on_disconnect = [](const std::string &, unsigned) { LOG.fatal("You need to set a on disconnect function"); };

          public:
            AClient()
            {
                _isBind = false;
                _stop = false;
                _bufferSize = BUFFER_SIZE;
            }

            virtual ~AClient()
            {
                LOG.warning("Deleting Client");
            }

            IClient &Connect() override
            {
                _clientInfo.ip = "0.0.0.0";
                _clientInfo.port = DEFAULT_PORT;
                return *this;
            }

            IClient &Connect(unsigned port) override
            {
                _clientInfo.ip = DEFAULT_IP;
                _clientInfo.port = port;
                return *this;
            }

            IClient &Connect(const std::string &ip, unsigned port) override
            {
                _clientInfo.ip = ip;
                _clientInfo.port = port;
                return *this;
            }

            IClient &setTransferDataCallback(const std::function<void(IClient *, void *, unsigned int)> &func) override
            {
                _onReceived = func;
                return *this;
            }

            IClient &transferData(IClient *client, void *data, unsigned size) override
            {
                _onReceived(client, data, size);
                return *this;
            }

            IClient &setOnDisconnect(std::function<void(const std::string &, unsigned)> func) override
            {
                _on_disconnect = func;
                return *this;
            }

            IClient &Stop() override
            {
                _stop = true;
                return *this;
            }

            IClient &waitUntilDisconnect() override
            {
                while (!_stop);
                return *this;
            }

            IClient &setBufferSize(unsigned bufferSize) override
            {
                _bufferSize = bufferSize;
                return *this;
            }

            IClient &addPipeline(const std::string &name, const std::function<bool(IClient *, void *, unsigned)> &function) override
            {
                _pipelines.emplace_back(name, function);
                return *this;
            }
        };
    }
}

