#include "TestServerUDP.hpp"

int main()
{
    Alfred::Network::IClient *server = new testServerUDP();

    server->Connect(8000);
    server->setTransferDataCallback([&] (Alfred::Network::IClient *, void *, unsigned) {
        std::cout << "HEY" << std::endl;
    });

    server->Listen();
}
