#include <cstdlib>
#include <iostream>
#include <arpa/inet.h>
#include <iwlib.h>
#include <pthread.h>

#include "../common/socket.h"
#include "../common/json/json.h"
#include "../common/protocol.h"
#include "Pools.h"

using namespace std;

std::map<pid_t, User *> users; // les utilisateurs
Pools *pools; // les salles de jeu

std::map<std::string, Pool *> waitedIps; // adresses IP attendues
std::map<std::string, Pool *>::iterator waitedIpsIt;

void *handleUser(void *param);

int main(int argc, char **argv) {

    int port; // port du serveur
    int sockfd; // point de connexion

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

    // --- Attente des joueurs

    cout << "> Attente d'un client... " << endl;

    while (true) {
        pthread_t threadId;
        int client;
        struct sockaddr_in addr;
        unsigned int addr_size = sizeof(struct sockaddr);

        if ((client = accept(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_size)) == -1) {
            perror("FAILURE");
            continue;
        }


        threadId = users.size();
        users[threadId] = new User();
        users[threadId]->setSocket(client);
        users[threadId]->setAddress(addr);

        printf("> L'utilisateur %p vient de se connecter au serveur\n", users[threadId]);

        if (pthread_create(&threadId, nullptr, handleUser, nullptr) != 0) {
            perror("pthread_create");
            continue;
        }
    }

    return EXIT_SUCCESS;
}

void *handleUser(void *) {
    User* currentUser = users.at(users.size() - 1);

    printf("> L'utilisateur %p a été affecté dans un nouveau thread\n", currentUser);

    return nullptr;
}
