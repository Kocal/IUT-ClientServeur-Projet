#include <cstdlib>
#include <iostream>
#include <arpa/inet.h>
#include <iwlib.h>
#include <pthread.h>
#include <map>
#include <vector>
#include <algorithm>

#include "../common/socket.h"
#include "../common/json/json.h"
#include "../common/protocol.h"
#include "Pools.h"

using namespace std;

std::map<pid_t, User *> users; // les utilisateurs
Pools *pools; // les salles de jeu

//std::map<std::string, Pool *> waitedIps; // adresses IP attendues
//std::map<std::string, Pool *>::iterator waitedIpsIt;

std::vector<std::string> waitedIps;

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

//        printf("> Nouvelle connexion sur %s:%d\n", user->getIpAddress(), user->getPort());
//
//        waitedIpsIt = waitedIps.find(user->getIpAddress());
//
//        cout << "ADD SIZE : " << waitedIps.size() << endl;
//
//        // L'adresse IP n'est pas attendue par un autre joueur
//        if (waitedIpsIt == waitedIps.end()) {
//            pool = pools->getEmptyPool();
//
//            printf("> Le joueur %p (%s) vient de rejoindre une pool vide (%p)\n", user, user->getIpAddress(),
//                   pool);
//
//            if (pool->addPlayer(user)) {
////                        response["code"];
//            } else {
////                        response["code"];
//            }
//
//            request["method"] = PROTOCOL_METHOD_NEW_GAME;
//        } else {
//            pool = pools->findByWaitedIp(user->getIpAddress());
//
//            printf("> Le joueur %p (%s) est attendu pour jouer dans une pool (%p)", user, user->getIpAddress(),
//                   waitedIpsIt->second);
//
//            request["method"] = PROTOCOL_METHOD_JOIN_POOL;
//
//            waitedIps.erase(waitedIpsIt);
//        }
//
//        user->send(fastWriter.write(request));
//
//        while (true) {
//            if (!reader.parse(user->recv(BUFFER_LENGTH), response)) {
//                cerr << "> Impossible de parser la réponse du client" << endl;
//                continue;
//            }
//
//            cout << "Réponse client (JSON) : " << response << endl;
//
//            switch (method) {
//                case PROTOCOL_METHOD_NEW_GAME: {
//                    cout << "> Création de la nouvelle partie" << endl;
//                    cout << pool << endl;
//
//                    pool->initGame(response["params"]["sideSize"].asInt(),
//                                   response["params"]["pionsCount"].asInt());
//                    pool->shouldWait(response["params"]["ipToWait"].asCString());
//
//                    waitedIps[response["params"]["ipToWait"].asCString()] = pool;
//
//                    break;
//                }
//
//                default:
//                    cout << "Commande inconnue" << endl;
//
//            }
//
//            break;

    }

    return EXIT_SUCCESS;
}

void *handleUser(void *) {
    User* currentUser = users.at(users.size() - 1);
    Pool* currentPool = nullptr;

    // Servira pour l'envoi de la requête au client
    std::string requestBuffer;
    Json::Value request;

    // Servira pour la réponse du client
    std::string responseBuffer;
    Json::Value response;

    // Facilite la vie :-)
    Json::Reader reader;
    Json::FastWriter writer;

    // On pourrait en avoir besoin plus tard
    char *currentUserIpAddress = currentUser->getIpAddress();

    int method;

    printf("> L'utilisateur %p a été affecté dans un nouveau thread\n", currentUser);

    // --- On vérifie si oui ou non l'utilisateur est attendu dans une pools

    std::vector<std::string>::iterator position = std::find(waitedIps.begin(), waitedIps.end(), currentUserIpAddress);

    // Pas attendu
    if(position == waitedIps.end()) {
        currentPool = pools->getEmptyPool();

        printf("> L'utilisateur %p a rejoint la pool vide %p\n", currentUser, currentPool);

        // hack malicieux temporaire pour tester si l'adresse IP est attendue
        waitedIps.push_back(currentUser->getIpAddress());

    } else { // attendu
        currentPool = pools->findByWaitedIp(currentUserIpAddress);

        printf("> L'utilisateur %p est attendu dans la pool %p\n", currentUser, currentPool);

        waitedIps.erase(position);
    }

    return nullptr;
}
