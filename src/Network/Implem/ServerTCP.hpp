/*
** UnixServer.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/UnixServer.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Sep 08 16:12:28 2017 Dimitri Wyzlic
** Last update Fri Sep 08 16:12:28 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_UNIXSERVER_HPP
#define ALFRED_UNIXSERVER_HPP

#include <cstring>
#include <sys/ioctl.h>
#include "IServer.hpp"

namespace Alfred
{
    class ServerTCP : public IServer
    {
    private:
        struct ConnectionInfo _currentClient;
        fd_set _rfds;
        socklen_t _sizeCurrentClient = sizeof(_currentClient.in);

        void _bind()
        {
            _info.in.sin_addr.s_addr = INADDR_ANY;
            _info.in.sin_family = AF_INET;
            _info.in.sin_port = htons(_info.port);
            _info.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
            if (_info.fd == -1)
                LOG.fatal("Socket creation error"); //TODO add perror
            if (bind(_info.fd, (const struct sockaddr *)(&_info.in), sizeof(_info.in)) == -1)
                throw BindFailed(_info.ip, _info.port);
            if ((listen(_info.fd, _info.port)) == -1)
                LOG.fatal("Listen failed");
        }

        void _accept()
        {
            _currentClient.fd = accept(_info.fd, (struct sockaddr *)&(_currentClient.in),
                                       &_sizeCurrentClient);
        }

        const char *_receive()
        {
            struct PacketHeader header;
            int to_read;
            ssize_t index;
            char *buff = new char[_packetSize * sizeof(char)];
            std::string *out = new std::string("");

            while (!_stop) { //TODO A VIRER
                bzero(buff, _packetSize);
//                if ((index = read(_currentClient.fd, buff, _packetSize)) <= 0) {
                if ((index = read(_currentClient.fd, &header, sizeof(struct PacketHeader))) <= 0) {
                    if (index < 0)
                        LOG.error("Failed to read");
                    close(_currentClient.fd);
                    printf("Client %d Disconnected\n", _currentClient.fd);
                    //TODO ADD AN _disconnect FUNCTION
                    _on_disconnect(this, _currentClient.fd);
                    _clients.erase(_currentClient.fd);
                    delete (buff);
                    return (nullptr);
                }

                LOG.debug("SIZE OF PACKET IS: " + std::to_string(header.length));

                if (index < sizeof(struct PacketHeader))
                    LOG.fatal(
                        "Unknown error during read invalid header size ? Use Alfred Client please to send msg or set the length option to false");

                if ((index = read(_currentClient.fd, buff, _packetSize - sizeof(struct PacketHeader))) <= 0) {
                    if (index < 0)
                        LOG.error("Failed to read 2");
                    close(_currentClient.fd);
                    printf("Client %d Disconnected 2\n", _currentClient.fd);
                    _on_disconnect(this, _currentClient.fd);
                    _clients.erase(_currentClient.fd);
                    delete (buff);
                    return (nullptr);
                }
                *out += buff;
                to_read = header.length - index;

                while (to_read > 0) //TODO CHECK IF MULTIPLE PACKET AND ADD QUEUE
                {
                    bzero(buff, _packetSize);
                    if ((index = read(_currentClient.fd, buff, _packetSize)) <= 0) {
                        if (index < 0)
                            LOG.error("Failed to read 3");
                        close(_currentClient.fd);
                        printf("Client %d Disconnected 3\n", _currentClient.fd);
                        _on_disconnect(this, _currentClient.fd);
                        _clients.erase(_currentClient.fd);
                        delete (buff);
                        return (nullptr);
                    }
//                    LOG.error("CUR BUFF RECU: " + std::string(buff));
                    *out += buff;
                    to_read -= index; //TODO FRAGMENTER PLEINS PACKET SI to_read < 0
                }
                out[header.length] = '\0';
                LOG.error("G RECU: " + *out);
                delete (buff);
                return out->c_str();
            }
        }

        void select_check()
        {
            struct ConnectionInfo tmp;

            int index = -1;
            while (++index < FD_SETSIZE) {
                if (FD_ISSET(index, &_rfds)) {
                    if (index == _info.fd) {
                        //New client
                        _accept();
                        tmp.in = _currentClient.in;
                        tmp.fd = _currentClient.fd;
                        this->_clients[_currentClient.fd] = ClientInfo(tmp);
                        printf("Client %d Connected\n", _currentClient.fd);
                        _first_connect(this, tmp.fd);
                    } else {
                        //Returning client
                        _currentClient.fd = index;
                        tmp.in = _currentClient.in;
                        tmp.fd = _currentClient.fd;
                        //Handle
                        const char *msg = _receive();
                        if (msg != nullptr)
                            _on_received(this, tmp.fd, msg);
                    }
                }
            }
        }

    public:

        ServerTCP() :
            IServer()
        {
            _bind();
        }

        explicit ServerTCP(const size_t port) :
            IServer(port)
        {
            _bind();
        }

        ServerTCP(const std::string &ip, const size_t port) :
            IServer(ip, port)
        {
            _bind();
        }

        IServer &Send(int clientID, const char *msg) override
        {
            dprintf(_clients[clientID].getFD(), "%s", msg);
            return *this;
        }

        IServer &run() override
        {
            struct timeval tv = {};
            int retval;

            while (!_stop) {
                tv.tv_usec = 0;
                tv.tv_sec = 0;
                FD_ZERO(&_rfds);
                for (const auto &it : _clients)
                    FD_SET(it.second.getFD(), &_rfds);
                FD_SET(_info.fd, &_rfds);
                if ((retval = select(_clients.size() + _info.fd + 2,
                                     &_rfds, NULL, NULL, &tv)) == -1 && !_stop)
                    LOG.fatal("Select failed"); //TODO CUSTOM EXCEPTION
                else if (retval >= 0)
                    select_check();
            }
            return *this;
        }
    };
}

#endif //ALFRED_UNIXSERVER_HPP
