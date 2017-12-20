#include "TestClientUDP.hpp"

int main()
{
    Alfred::Network::IClient *client = new testClientUDP();

//    client->Connect(8000); //ONLY TO RECEIVE MSG

    std::string toSend = "salut";

    client->SendTo("127.0.0.1", 8000, (void *)toSend.c_str(), toSend.size());
}