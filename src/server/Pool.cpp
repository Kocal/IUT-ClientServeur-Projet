//
// Created by kocal on 02/04/16.
//

#include "Pool.h"

Pool::Pool(int nbPlayers) : nbPlayers(nbPlayers) {

    users = std::vector<User *>(nbPlayers);

}

