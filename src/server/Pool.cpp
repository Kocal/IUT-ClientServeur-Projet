//
// Created by kocal on 02/04/16.
//

#include <iostream>
#include "Pool.h"

Pool::Pool(int nbPlayers) : nbPlayers(nbPlayers) {
    this->users = std::vector<User *>(nbPlayers);
}

int Pool::getCurrentNbPlayers() {
    int _players = 0;

    for (std::vector<User *>::iterator it = this->users.begin(); it != this->users.end(); it++) {
        if (*it != nullptr) {
            _players++;
        }
    }

    return _players;
}

bool Pool::isEmpty() {
    return this->getCurrentNbPlayers() == 0;
}

bool Pool::isFull() {
    return this->getCurrentNbPlayers() == this->nbPlayers;
}
