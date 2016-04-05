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

    int getCurrentNbPlayers();

    bool isEmpty();

    bool isFull();

    bool addPlayer(User *pUser);

    bool isWaitingForIpAddress(const char *ipAddress);

    void shouldWait(const char *ipAddress);

    void shouldNotWait(const char *ipAddress);

    void initGame(int sideSize, int pionsToAlignCount);

private:

    int nbPlayers;

    int sideSize;
    int pionsToAlignCount;

    std::vector<User *> users;
    std::vector<const char *> waitedIpAddress;
};


#endif //IUT_CLIENTSERVEUR_MINIPROJET_POOL_H
