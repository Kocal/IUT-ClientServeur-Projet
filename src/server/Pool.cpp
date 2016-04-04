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

bool Pool::addPlayer(User *pUser) {
    if(this->isFull()) {
        return false;
    }

    this->users.push_back(pUser);
    return true;
}

bool Pool::isWaitingForIpAddress(const char *ipAddress) {
    for(std::vector<const char*>::iterator it = this->waitedIpAddress.begin(); it != this->waitedIpAddress.end(); it++) {
        std::cout << (*it) << std::endl;
    }
}

void Pool::shouldWait(const char *ipAddress) {
    this->waitedIpAddress.push_back(ipAddress);
}

void Pool::initGame(int sideSize, int pionsToAlignCount) {
    this->sideSize = sideSize;
    this->pionsToAlignCount = pionsToAlignCount;


}


