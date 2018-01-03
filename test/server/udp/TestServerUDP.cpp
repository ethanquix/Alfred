#include "TestServerUDP.hpp"

int main()
{
    Alfred::Network::IAuthenticator auth;

    auth.setAnalyzeFunc([] (Alfred::Network::IAuthenticator *, void *msg, unsigned bytes) -> void {
        std::cout << "[AUTH SYSTEM] On m'a appellé avec " << std::string((char *)msg, bytes) << std::endl;
    });

    Alfred::Network::IClient *server = new testServerUDP();

    server->addPipeline("auth pipeline", [&] (Alfred::Network::IClient *, void *msg, unsigned bytes) -> bool {
        auth.analyze(msg, bytes);
        return true;
    });

    server->Connect(8000);
    server->setTransferDataCallback([&] (Alfred::Network::IClient *c, void *msg, unsigned bytes) {
        std::string m((char *)msg, bytes);

        std::cout << m << std::endl;

        std::cout << c->getInfos().ip << ":" << c->getInfos().port << std::endl;
    });

    server->Listen();
}
