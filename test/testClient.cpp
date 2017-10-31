/*
** test_Client.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/test_Client.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Sat Sep 16 17:58:26 2017 Dimitri Wyzlic
** Last update Sat Sep 16 17:58:26 2017 Dimitri Wyzlic
*/

#include "testClient.hpp"

int main()
{
    Alfred::Network::IClient *client = new testClient();

    client->Connect(8000);
    client->Listen();

    delete(client);
}

testClient::testClient() = default;

Alfred::Network::IClient &testClient::onReceived()
{
    auto *out = new char[3];
//    LOG.warning(std::to_string(readXChar(out, 2)));
//    out[3]  = '\0';
    int ret = readUntil(out, 'A');

    LOG.warning("Ret : " + std::to_string(ret));
    std::string final(out, ret + 1);

    LOG.warning("Msg " + final);
    return *this;
}