#include <cstdlib>
#include <iostream>

#include <cstdio>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../common/socket.h"
#include "../common/cause.h"
#include "../common/util.h"

// #define PORT 8080 // Port d'écoute
#define MAX_GAME 4
#define MAX_PLAYERS_PER_GAME 2 // Nombre maximum de clients/joueurs

using namespace std;

int main(int argc, char **argv) {
    
    int port; // port du serveur
    int sockfd; // point de connexion
    int **rooms; // salles de jeu 

    // --- Vérification du port

    if(argc < 2 || sscanf(argv[1], "%d", &port) != 1) {
        port = 8080;
        printf("> Usage : %s <port>\n", argv[0]);
        printf("> Utilisation du port %d par défaut\n", port);
    } else {
        printf("> Utilisation du port %d\n", port);
    }

    // --- Création du point de connexion

    printf("> Création d'un point de connexion... ");
    sockfd = creer_point_connexion(port);
    
    if(sockfd < 0) {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    } else {
        printf("OK\n");
    }

    // --- Attente des clients
    init2DimArray(rooms, MAX_GAME, MAX_PLAYERS_PER_GAME);
    
    

    return EXIT_SUCCESS;
}

