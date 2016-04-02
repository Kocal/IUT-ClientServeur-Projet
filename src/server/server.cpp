#include <cstdlib>
#include <iostream>

#include "../common/socket.h"

#include "Pools.h"

using namespace std;

int main(int argc, char **argv) {

    int port; // port du serveur
    int sockfd; // point de connexion
    // salles de jeu

    // --- Vérification du port

    if (argc < 2 || sscanf(argv[1], "%d", &port) != 1) {
        port = 8080;
        printf("> Usage : %s <port>\n", argv[0]);
        printf("> Utilisation du port %d par défaut\n", port);
    } else {
        printf("> Utilisation du port %d\n", port);
    }

    // --- Création du point de connexion

    cout << "> Création d'un point de connexion... ";
    sockfd = creer_point_connexion(port);

    if (sockfd < 0) {
        cout << "FAILURE" << endl;
        return EXIT_FAILURE;
    } else {
        cout << "OK\n";
    }

    // --- Attente des clients
    cout << "> Création des pools... ";

    Pools *pools = new Pools();

    printf("%d pools de %d joueurs ont étés créés", pools->getNbPools(), pools->getNbPlayers());
    //initPools(pools, MAX_POOLS, MAX_PLAYERS);

    //int* emptyPool = findPool(pools, POOL_FIND_MODE::EMPTY);

    return EXIT_SUCCESS;
}
