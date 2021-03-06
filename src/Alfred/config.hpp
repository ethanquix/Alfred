#pragma once

namespace Alfred
{
    //Server
    namespace Network
    {
        constexpr static char DEFAULT_IP[] = "0.0.0.0";
        constexpr static unsigned DEFAULT_PORT = 8000;
        constexpr static bool KEEP_ALIVE = true;
        constexpr static unsigned BUFFER_SIZE = 1024;
        constexpr static unsigned MAX_ID = 1000000;
        constexpr static int INDICATOR_DISCONNECT = -1;
        constexpr static unsigned IDENTIFIER_SIZE = 12;
        constexpr static unsigned AUTH_HEADER_SIZE = 10;
    }

    //Random
    namespace Random
    {
        constexpr static char RANDOM_STRING_CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    }

    namespace Ecs
    {
#define ECS_MULTIMAP_SINGLETON false
        constexpr static unsigned MAX_COMPONENTS = 64;
        constexpr static unsigned MAX_SYSTEMS = 64;
        constexpr static unsigned ENTITIES_RESERVED = 10000;
    }
}

//Server
#define PLACEHOLDER_TRANSFER_DATA_CALLBACK Alfred::Network::IClient *client, void *msg, unsigned size