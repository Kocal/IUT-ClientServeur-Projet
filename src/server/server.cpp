#include <cstdlib>
#include <iostream>
#include <arpa/inet.h>
#include <iwlib.h>
#include "../common/socket.h"
#include "../common/json/json.h"
#include "Pools.h"
#include "../common/protocol.h"

using namespace std;

int main(int argc, char **argv) {

    int port; // port du serveur
    int sockfd; // point de connexion
    Pools *pools; // les salles de jeu

    pid_t pid;

    std::map<std::string, Pool *> waitedIps; // adresses IP attendues
    std::map<std::string, Pool *>::iterator waitedIpsIt;

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

//    cout << "> Recherche d'une salle vide... ";
//    Pool *pool = pools->getEmptyPool();
//
//    if (pools == nullptr) {
//        cout << "FAILURE" << endl;
//        return EXIT_FAILURE; // changer ça
//    } else {
//        cout << "OK" << endl;
//    }

    // --- Attente des joueurs

    cout << "> Attente d'un client... " << endl;

    while (true) {
        int client;
        struct sockaddr_in addr;
        unsigned int addr_size = sizeof(struct sockaddr);


        if ((client = accept(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_size)) == -1) {
            perror("FAILURE");
            continue;
        }

        pid = fork();

        switch (pid) {
            case -1: // error
                perror("> fork()");
                exit(EXIT_FAILURE);

            case 0: // child {

                User *user = new User();
                user->setSocket(client);
                user->setAddress(addr);

                std::string responseBuffer;
                Json::Value response;
                Json::Reader reader;
                Json::FastWriter fastWriter;

                printf("> Nouvelle connexion sur %s:%d\n", user->getIpAddress(), user->getPort());

                waitedIpsIt = waitedIps.find(user->getIpAddress());

                // L'adresse IP n'est pas attendue par un autre joueur
                if (waitedIpsIt == waitedIps.end()) {
                    printf("> Le joueur %p (%s) vient de rejoindre une pool vide (%p)\n", user, user->getIpAddress(),
                           pools->getEmptyPool());

                    response["method"] = PROTOCOL_METHOD_NEW_GAME;
                } else {
                    printf("> Le joueur %p (%s) est attendu pour jouer dans une pool (%p)", user, user->getIpAddress(),
                           waitedIpsIt->second);

                    response["method"] = PROTOCOL_METHOD_JOIN_POOL;
                    waitedIps.erase(waitedIpsIt);
                }

                user->send(fastWriter.write(response));

                while (true) {
                    cout << "Réponse : " << user->recv(100) << endl;
                    break;
                }
        }
    }

    return EXIT_SUCCESS;
}
