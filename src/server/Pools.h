#ifndef _POOL_H
#define _POOL_H

#include "../common/conf.h"
#include "Pool.h"
#include <map>
#include <vector>

struct POOL_FIND_MODE {
    const static int EMPTY = 0;
    const static int WAITING = 1;
    const static int FULL = 2;
};

class Pools {

public:

    Pools(int nbPools = MAX_POOLS, int nbPlayers = MAX_PLAYERS);

    /**
     * Retourne une pool vide
     */
    Pool *getEmptyPool();

    /**
     * Retourne la pool où `ipAddress` est attendue
     */
    Pool *findByWaitedIp(char *ipAddress);

    int getNbPools() const {
        return nbPools;
    }

    int getNbPlayers() const {
        return nbPlayers;
    }

private:

    int nbPools;
    int nbPlayers;

    std::vector<Pool *> pools;

    void initPools();
};

#endif
