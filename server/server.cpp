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

#define PORT 8080 // Port d'écoute
#define MAX_PLAYERS 2 // Nombre maximum de clients/joueurs

using namespace std;

int main() {
    int sockfd, players[MAX_PLAYERS];

    sockfd = creer_point_connexion(PORT);
    
    cout << "Hello world!" << endl;

    return EXIT_SUCCESS;
}
