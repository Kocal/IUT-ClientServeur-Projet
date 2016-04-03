//
// Created by kocal on 02/04/16.
//

#include "User.h"
#include <iostream>

#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

User::User(int socket) : socket(socket) { }

std::string User::recv(unsigned int bytes) {
    std::string output(bytes, 0);

    if (read(this->socket, &output[0], bytes - 1) < 0) {
        std::cerr << "Impossible de lire les données de la socket" << std::endl;
    }

    return output;
}

void User::send(std::string str) {
    if(write(this->socket, str.c_str(), strlen(str.c_str())) == -1) {
        std::cerr << "Impossible d'écrire des données dans la socket" << std::endl;
    }
}

void User::setAddress(sockaddr_in in) {
    this->addr = in;
}
