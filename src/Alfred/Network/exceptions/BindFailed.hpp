#pragma once

#include <string>
#include <exception>

namespace Alfred
{
    namespace Network
    {
        class BindFailed : public std::exception
        {
            std::string msg;
          public:
            BindFailed(const std::string &ip, int port) :
                msg(std::string("Failed to bind to ip: ") + ip + " and port " + std::to_string(port))
            {}

            const char *what() const throw() override
            { return msg.c_str(); }
        };
    }
}