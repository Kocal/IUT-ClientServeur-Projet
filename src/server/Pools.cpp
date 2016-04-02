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




