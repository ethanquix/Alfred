#include "TestClientUDP.hpp"

int main()
{
    Alfred::Network::IClient *client = new testClientUDP();

    client->Connect(8000);

    std::string toSend = "salut";

    client->Send((void *)toSend.c_str(), toSend.size());
}