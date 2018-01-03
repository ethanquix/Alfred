#pragma once

#include <unordered_map>
#include <functional>
#include <AlfredBase/Logger/Logger.hpp>

namespace Alfred
{
    namespace Network
    {
        class IAuthenticator
        {
          private:
            // Map of pseudo and clientAuth (token)
            std::unordered_map<std::string, std::string> _clients;
            std::function<void(IAuthenticator *, void *msg, unsigned len)> _analyzeFunc = [] (IAuthenticator *, void *msg, unsigned len) -> void {
                LOG.fatal("You need to set the analyzeFunc of IAuthenticator");
            };

          public:
            IAuthenticator() = default;

            void analyze(void *msg, unsigned len)
            {
                _analyzeFunc(this, msg, len);
            }

            void registerPseudoToken(const std::string &pseudo, const std::string &token)
            {
                _clients[pseudo] = token;
            }

            bool deletePseudo(const std::string &pseudo)
            {
                return _clients.erase(pseudo) >= 1;
            }

            bool auth(const std::string pseudo, const std::string &token)
            {
                return _clients.count(pseudo) > 0 && _clients[pseudo]== token;
            }

            template <typename Fctor>
            void setAnalyzeFunc(Fctor &&func)
            {
                _analyzeFunc = func;
            }
        };
    }
}