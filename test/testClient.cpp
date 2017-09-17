/*
** test_Client.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/test_Client.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Sat Sep 16 17:58:26 2017 Dimitri Wyzlic
** Last update Sat Sep 16 17:58:26 2017 Dimitri Wyzlic
*/

#include <Implem/ClientTCP.hpp>

int main()
{
    Alfred::ClientTCP client;

    client.onReceived([] (Alfred::IClient *c, const char *msg) {
        std::cout << "I received: " << msg << std::endl;
        c->Send("Reponse du client\n");
    });

//    client.Connect();

    //TODO Implement run method

    client.run();
}