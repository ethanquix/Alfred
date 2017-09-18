/*
** ClientTCP.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/ClientTCP.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Sep 13 16:13:32 2017 Dimitri Wyzlic
** Last update Wed Sep 13 16:13:32 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_CLIENTTCP_HPP
#define ALFRED_CLIENTTCP_HPP

#include <cstring>
#include "Logger.hpp"
#include "IClient.hpp"

namespace Alfred
{
    class ClientTCP : public IClient
    {
    private:
        fd_set rdfs = {};

        void _bind()
        {
            _info.in.sin_addr.s_addr = INADDR_ANY;
            _info.in.sin_family = AF_INET;
            _info.in.sin_port = htons(_info.port);
            _info.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
            if (_info.fd == -1)
                LOG.fatal("Socket creation error"); //TODO add perror
            if (connect(_info.fd, (const struct sockaddr *)(&_info.in), sizeof(_info.in)) == -1)
                throw BindFailed(_info.ip, _info.port);
        }

        const char *_receive_helper_dc(int index)
        {
            if (index < 0)
                LOG.error("Failed to read");
            close(_info.fd);
            printf("Server %d Disconnected\n", _info.fd);
            stop();
            _on_disconnect();
            return (nullptr);
        }

        const char *_receive()
        {
            int to_read = 0;
            ssize_t index;
            std::string *out = new std::string("");

            while (!_stop) { //TODO A VIRER
                if ((index = read(_info.fd, &to_read, _lengthIndicatorSize)) <= 0) {
                    return _receive_helper_dc(index);
                }
                to_read = ntohl(to_read);
                if (index < _lengthIndicatorSize)
                    LOG.fatal(
                        "Unknown error during read invalid header size ? Use Alfred Client please to send msg or set the length option to false");
                char *buff = new char[(to_read + 1) * sizeof(char)];
                while (to_read > 0) {
                    LOG.error("Hey je passe dans la boucle 3 " + std::to_string(to_read));
                    bzero(buff, (to_read + 1) * sizeof(char));
                    if ((index = read(_info.fd, buff, to_read)) <= 0) {
                        delete (buff);
                        return _receive_helper_dc(index);
                    }
                    buff[index] = '\0';
                    *out += buff;
                    to_read -= index;
                }
//                out->resize(size); //TODO FIX [TODONE] ?
                LOG.error("G RECU: " + *out);
                delete (buff);
                return out->c_str();
            }
        }

        void select_check()
        {
            const char *msg = _receive();
            if (msg)
                _onReceived(this, msg);
        }

    public:
        ClientTCP() : IClient()
        {}

        explicit ClientTCP(const size_t port) : IClient(port)
        {}

        ClientTCP(const std::string &ip, const size_t port) : IClient(ip, port)
        {}

        IClient &Connect() override
        {
            _isBind = false;
            _bind();
            _isBind = true;
            return *this;
        }

        IClient &Connect(const std::string &ip, const size_t port) override
        {
            _isBind = false;
            _info.ip = ip;
            _info.port = port;
            _bind();
            _isBind = true;
            return *this;
        }

        IClient &Listen() override
        {
            int retval;

            if (!_isBind)
                LOG.fatal("You need to call Connect before call Listen");
            while (!_stop) {
                FD_ZERO(&rdfs);
                FD_SET(_info.fd, &rdfs);
                retval = select(_info.fd + 1, &rdfs, NULL, NULL, NULL);
                if (retval == -1)
                    LOG.fatal("Select failed"); //TODO CUSTOM EXCEPTION
                else if (retval >= 0)
                    select_check();
            }
            close(_info.fd);
            return *this;
        }

        //TODO CHANGE RECEIVE METHOD BY LENGTH OR FIXED LENGTH
        IClient &Send(const char *msg) override //TODO CHANGE PROTO BY VOID * AND SIZE_T LENGTH
        {
            std::string data(msg);
            int size = htonl(data.size());

            write(_info.fd, (const char *)&size, _lengthIndicatorSize);
            write(_info.fd, data.data(), data.size());
            return *this;
        }

        IClient &sendThenListen(const char *msg) override
        {
            if (!_isBind)
                LOG.fatal("You need to call Connect before call Listen");
            Send(msg);
            Listen();
            return *this;
        }
    };
}

#endif //ALFRED_CLIENTTCP_HPP
