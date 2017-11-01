/*
** config.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/config.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Mon Sep 18 01:23:13 2017 Dimitri Wyzlic
** Last update Mon Sep 18 01:23:13 2017 Dimitri Wyzlic
*/

#pragma once

namespace Alfred
{
    //Server
    constexpr size_t MAX_SIZE_IP = 16;

    namespace Network
    {
        constexpr static char DEFAULT_IP[] = "0.0.0.0";
        constexpr static unsigned DEFAULT_PORT = 8000;
        constexpr static bool KEEP_ALIVE = true;
        constexpr static unsigned BUFFER_SIZE = 1024;
        constexpr static unsigned MAX_ID = 1000000;
        constexpr static int INDICATOR_DISCONNECT = -1;
    }

    //Random
    namespace Random
    {
        constexpr static char RANDOM_STRING_CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    }
}

//Server
#define PLACEHOLDER_TRANSFER_DATA_CALLBACK Alfred::Network::IClient *client, void *msg, unsigned size