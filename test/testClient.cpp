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

    client->setTransferDataCallback([&] (Alfred::Network::IClient *c, void *msg, unsigned size) {
        LOG.warning("Msg " + std::string((char *)msg, size + 1));
    });

    client->AsyncListen();
    client->waitUntilDisconnect();

    delete(client);
}

Alfred::Network::IClient &testClient::onNewMessage(){
    auto *out = new char[3];
//    LOG.warning(std::to_string(readXChar(out, 2)));
//    out[3]  = '\0';
    int ret = readUntil(out, 'A');
    transferData(this, out, ret);
    return *this;
}