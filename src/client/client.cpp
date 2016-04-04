#include <cstdlib>
#include <iostream>
#include "../common/conf.h"
#include "../common/protocol.h"
#include "../common/socket.h"
#include "../common/json/json.h"
#include <iwlib.h>

using namespace std;

int main(int argc, char **argv) {

    string server_url;
    int port;
    int socket;

    char responseBuffer[BUFFER_LENGTH];

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
        int method;

        Json::Value response;
        Json::Value request;
        Json::Reader reader;
        Json::FastWriter fastWriter;

        bzero(&responseBuffer, BUFFER_LENGTH);
        read(socket, &responseBuffer, BUFFER_LENGTH);

        if (!reader.parse(responseBuffer, response)) {
            cerr << "> Impossible de parser la réponse du serveur" << endl;
            continue;
        }

        cout << "Réponse : " << responseBuffer << endl;
        cout << "Réponse (JSON) : " << response << endl;

        method = response.get("method", PROTOCOL_NO_METHOD).asInt();

        switch (method) {
            case PROTOCOL_METHOD_NEW_GAME: {
                cout << "> Création d'une nouvelle partie" << endl;

                int paramPionsCount = 3;
                int paramSideSize = 4;
                string paramIpToWait;

                do {
                    cout << "> Nombre de pions à aligner pour gagner (>=3): ";
                    cin >> paramPionsCount;

                    cout << "> Taille des côtés du plateau (>=" << paramPionsCount << ") : ";
                    cin >> paramSideSize;

                    cout << "> Adresse IP du joueur à attendre : ";
                    cin >> paramIpToWait;
                } while (paramPionsCount < 3 || paramSideSize < paramPionsCount);

                request["method"] = PROTOCOL_METHOD_NEW_GAME;
                request["params"]["pionsCount"] = paramPionsCount;
                request["params"]["sideSize"] = paramSideSize;
                request["params"]["ipToWait"] = paramIpToWait;

                write(socket, fastWriter.write(request).c_str(), BUFFER_LENGTH);

                break;
            }

            case PROTOCOL_METHOD_JOIN_POOL: {
                cout << "Je rejoins une partie" << endl;
            }

            default:
                cout << "Commande inconnue" << endl;
        }


    }
    return EXIT_SUCCESS;
}
