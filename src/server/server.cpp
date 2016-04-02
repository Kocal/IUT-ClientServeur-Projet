#include <cstdlib>
#include <iostream>

#include "../common/socket.h"

#include "Pools.h"

using namespace std;

int main(int argc, char **argv) {

    int port; // port du serveur
    int sockfd; // point de connexion
    Pools *pools;

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
        cout << "OK" << endl;
    }

    // --- Création des pools

    cout << "> Création des pools... ";

    pools = new Pools();
    printf("%d pools de %d joueurs ont étés créés\n", pools->getNbPools(), pools->getNbPlayers());

    cout << "> Recherche d'une salle vide... ";
    Pool *pool = pools->getEmptyPool();

    if (pools == nullptr) {
        cout << "FAILURE" << endl;
        return EXIT_FAILURE; // changer ça
    } else {
        cout << "OK" << endl;
    }

    return EXIT_SUCCESS;
}
