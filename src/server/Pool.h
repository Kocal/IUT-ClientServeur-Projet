//
// Created by kocal on 02/04/16.
//

#ifndef IUT_CLIENTSERVEUR_MINIPROJET_POOL_H
#define IUT_CLIENTSERVEUR_MINIPROJET_POOL_H

#include <vector>
#include "../common/conf.h"
#include "../common/User.h"

class Pool {

public:

    Pool(int nbPlayers = MAX_PLAYERS);

    bool isEmpty();

    bool isFull();

private:

    int nbPlayers;
    std::vector<User *> users;
};


#endif //IUT_CLIENTSERVEUR_MINIPROJET_POOL_H
