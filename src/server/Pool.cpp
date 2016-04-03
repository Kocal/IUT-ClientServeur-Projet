//
// Created by kocal on 02/04/16.
//

#include <iostream>
#include "Pool.h"

Pool::Pool(int nbPlayers) : nbPlayers(nbPlayers) {
    this->users = std::vector<User *>(nbPlayers);
}

bool Pool::isEmpty() {

    for (std::vector<User *>::iterator it = this->users.begin(); it != this->users.end(); it++) {
        if (*it != nullptr) { // On a au moins un joueur dans la pool
            return false;
        }
    }

    return true;
}

bool Pool::isFull() {
    bool isFull = true;

    for (std::vector<User *>::iterator it = this->users.begin(); it != this->users.end(); it++) {
        if (*it == nullptr) { // On a au moins un joueur dans la pool
            isFull = false;
            break;
        }
    }

    return isFull;
}
