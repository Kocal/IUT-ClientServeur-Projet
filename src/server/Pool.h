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

    /**
     * Retourne le nombre de joueurs dans la pool
     */
    int getCurrentNbPlayers();

    /**
     * Est-ce que la pool est vide ?
     */
    bool isEmpty();

    /**
     * Est-ce que la pool est pleine ?
     */
    bool isFull();

    /**
     * Ajoute un joueur dans la pool
     */
    bool addPlayer(User *pUser);

    /**
     * Ajoute une adresse IP à attendre
     */
    void shouldWait(const char *ipAddress);

    /**
     * Supprime une adresse IP qui était attendue
     */
    void shouldNotWait(const char *ipAddress);

    /**
     * Est-ce que `ipAddress` est attendue par la pool ?
     */
    bool isWaitingForIpAddress(const char *ipAddress);

    /**
     * Initialise une partie
     */
    void initGame(int sideSize, int pionsToAlignCount);

private:

    int nbPlayers;

    int sideSize;
    int pionsToAlignCount;

    std::vector<User *> users;
    std::vector<const char *> waitedIpAddress;
};

#endif //IUT_CLIENTSERVEUR_MINIPROJET_POOL_H
