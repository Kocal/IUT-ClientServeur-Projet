#include <cstdlib>
#include <iostream>
#include "../common/conf.h"
#include "../common/protocol.h"
#include "../common/socket.h"
#include <memory.h>

#include <iwlib.h>

using namespace std;

int main(int argc, char **argv) {

    string server_url;
    int port;
    int socket;

    char response[BUFFER_LENGTH];
    int responseCode;

    // --- Vérification de l'adresse du serveur et port

    if (argc < 3 || sscanf(argv[1], "%s", &server_url) != 1 || sscanf(argv[2], "%d", &port) != 1) {
        server_url = "127.0.0.1";
        port = 8080;

        printf("> Usage : %s <server_url> <port>\n", argv[0]);
        printf("> Utilisation de l'addresse '%s' par défaut\n", server_url.c_str());
        printf("> Utilisation du port '%d' par défaut\n", port);
    } else {
        printf("> Utilisation de l'addresse '%s'\n", server_url);
        printf("> Utilisation du port '%d'\n", port);
    }

    // --- Connexion au serveur

    cout << "> Connexion au serveur... ";

    socket = ouvrir_canal_communication(server_url.c_str(), port);
    if (socket < 0) {
        cout << "FAILURE" << endl;
        return EXIT_FAILURE;
    } else {
        cout << "OK" << endl;
    }

    for (; ;) {
        bzero(&response, BUFFER_LENGTH);
        read(socket, &response, BUFFER_LENGTH);

        cout << "Réponse : " << response << endl;

        if(strcmp(response, PROTOCOL_NEW_GAME) == 0) {
            cout << "> Création d'une nouvelle partie" << endl;

            int paramPionsCount = 3;
            int paramSideSize = 4;
            string paramIpToWait;

            do {
                cout << "> Nombre de pions à aligner pour gagner : ";
                cin >> paramPionsCount;

                cout << "> Taille des côtés du plateau (>=" << paramPionsCount << ") : ";
                cin >> paramSideSize;

                cout << "> Adresse IP du joueur à attendre : ";
                cin >> paramIpToWait;
            } while(paramPionsCount < 3 || paramSideSize < paramPionsCount);


        } else if(strcmp(response, PROTOCOL_JOIN_POOL) == 0) {
            cout << "Je rejoins une partie" << endl;
        } else {
            cout << "Commande inconnue" << endl;
        }
        break;
    }

    return EXIT_SUCCESS;
}
