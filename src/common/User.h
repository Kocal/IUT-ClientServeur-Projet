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

    /**
     * Permet de reçevoir n bytes du client
     */
    std::string recv(unsigned int bytes);

    /**
     * Permet d'envoyer une requête au client
     */
    void send(std::string string);

    void setSocket(int socket) {
        this->socket = socket;
    }

    void setAddress(sockaddr_in in);

    const sockaddr_in &getAddr() const {
        return addr;
    }

    char *getIpAddress() {
        return inet_ntoa(this->addr.sin_addr);
    }

private:
    int socket;
    sockaddr_in addr;
};

#endif //IUT_CLIENTSERVEUR_MINIPROJET_USER_H
