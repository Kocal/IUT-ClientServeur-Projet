#include <iostream>
#include <algorithm>
#include "Pool.h"

Pool::Pool(int nbPlayers) : nbPlayers(nbPlayers) {
//    this->users = std::vector<User *>(nbPlayers);
}


int Pool::getCurrentNbPlayers() {
    return this->users.size();
}

bool Pool::isEmpty() {
    return this->getCurrentNbPlayers() == 0;
}

bool Pool::isFull() {
    return this->getCurrentNbPlayers() == this->nbPlayers;
}

bool Pool::addPlayer(User *pUser) {
    if (this->isFull()) {
        return false;
    }

    this->users.push_back(pUser);
    return true;
}

void Pool::shouldWait(const char *ipAddress) {
    this->waitedIpAddress.push_back(ipAddress);
}

void Pool::shouldNotWait(const char *ipAddress) {
    auto position = std::find(this->waitedIpAddress.begin(), this->waitedIpAddress.end(), ipAddress);

    if (position != this->waitedIpAddress.end()) {
        this->waitedIpAddress.erase(position);
    }
}

bool Pool::isWaitingForIpAddress(const char *ipAddress) {
    std::vector<const char *>::iterator it;

    for (it = this->waitedIpAddress.begin(); it != this->waitedIpAddress.end(); it++) {
        if (ipAddress == *it) {
            return true;
        }
    }

    return false;
}

void Pool::initGame(int sideSize, int pionsToAlignCount) {
    this->sideSize = sideSize;
    this->pionsToAlignCount = pionsToAlignCount;

    //TODO: Faire des trucs ici
}
