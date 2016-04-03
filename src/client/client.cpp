#include <cstdlib>
#include <iostream>
#include "../common/socket.h"

using namespace std;

int main(int argc, char **argv) {

    string server_url;
    int port;
    int socket;

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

    cout << "Connexion au serveur... ";

    socket = ouvrir_canal_communication(server_url.c_str(), port);
    if(socket < 0) {
        cout << "FAILURE" << endl;
        return EXIT_FAILURE;
    } else {
        cout << "OK" << endl;
    }

    cout << "Client.cpp" << endl;
    return EXIT_SUCCESS;
}
