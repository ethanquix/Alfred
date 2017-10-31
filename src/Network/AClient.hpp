#pragma once

#include <thread>
#include "IClient.hpp"
#include "Logger.hpp"

namespace Alfred
{
    namespace Network
    {
        class AClient : public IClient
        {
          protected:
            unsigned _port;
            std::string _ip;
            bool _isBind;
            bool _stop;
            unsigned _bufferSize;

            std::function<void(IClient *, void *, unsigned)> _onReceived = [](IClient *, void *, unsigned) { LOG.fatal("You need to set a onReceived function"); };
            std::function<void(const std::string &)> _on_disconnect = [](const std::string &) { LOG.fatal("You need to set a on disconnect function"); };

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
                _ip = DEFAULT_IP;
                _port = DEFAULT_PORT;
                return *this;
            }

            IClient &Connect(unsigned port) override
            {
                _ip = DEFAULT_IP;
                this->_port = port;
                return *this;
            }

            IClient &Connect(const std::string &ip, unsigned port) override
            {
                this->_ip = ip;
                this->_port = port;
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

            IClient &onDisconnect(std::function<void(const std::string &)> func) override
            {
                _on_disconnect = func;
                return *this;
            }

            IClient &Stop() override
            {
                _stop = true;
                return *this;
            }

            IClient &setBufferSize(unsigned bufferSize) override
            {
                _bufferSize = bufferSize;
                return *this;
            }
        };
    }
}

