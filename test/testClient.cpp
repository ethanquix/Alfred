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
    Alfred::ClientTCP client(8001);

    client.onReceived([](Alfred::IClient *c, const char *msg) {
        std::cout << "I received: " << msg << std::endl;
//        c->Send("The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code. The problem is in your server side code.\n");
        c->Send("bonjour monsieur\0");
        sleep(2);
        c->stop();
    });

//    client.Connect();

    //TODO Implement run method

    client.run();
}