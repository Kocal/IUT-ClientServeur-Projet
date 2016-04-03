//
// Created by kocal on 02/04/16.
//

#ifndef IUT_CLIENTSERVEUR_MINIPROJET_USER_H
#define IUT_CLIENTSERVEUR_MINIPROJET_USER_H

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

class User {

public:
    User(int socket = 0);


    std::string recv(unsigned int bytes);
    void send(std::string string);

    int getSocket() const {
        return socket;
    }

    void setSocket(int socket) {
        this->socket = socket;
    }

    const sockaddr_in &getAddr() const {
        return addr;
    }

    void setAddress(sockaddr_in in);

    char *getIpAddress() {
        return inet_ntoa(this->addr.sin_addr);
    }

    int getPort() {
        return this->addr.sin_port;
    }

private:
    int socket;
    sockaddr_in addr;
};


#endif //IUT_CLIENTSERVEUR_MINIPROJET_USER_H
