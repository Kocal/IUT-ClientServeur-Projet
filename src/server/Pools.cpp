#include <iostream>
#include "Pools.h"

Pools::Pools(int nbPools, int nbPlayers) : nbPools(nbPools), nbPlayers(nbPlayers) {
    this->initPools();
}

void Pools::initPools() {
    int _pool;

    for (_pool = 0; _pool < this->nbPools; _pool++) {
        this->pools.push_back(new Pool(this->nbPlayers));
    }
}

Pool *Pools::getEmptyPool() {
    Pool *pool = nullptr;

    for (std::vector<Pool *>::iterator it = this->pools.begin(); it != this->pools.end(); it++) {
        if ((*it)->isEmpty()) {
            pool = *it;
            break;
        }
    }

    return pool;
}

Pool *Pools::findByWaitedIp(char *ipAddress) {
    Pool *pool = nullptr;

    for(std::vector<Pool *>::iterator it = this->pools.begin(); it != this->pools.end(); it++) {
        if((*it)->isWaitingForIpAddress(ipAddress)) {
            pool = *it;
            break;
        }
    }

    return pool;
}
