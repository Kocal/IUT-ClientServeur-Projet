#ifndef _SOCKET_H
#define _SOCKET_H

#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

extern volatile sig_atomic_t stop;

extern int creer_point_connexion(int port);
extern int ouvrir_canal_communication(char *serveur, int port);

// renvoie le nom de la machine et le port utilise par le client connecte a la socket "communication"
extern void adresse_client(char *client, int client_size, int *client_port, int communication);

// renvoie le nom de la machine locale et le port utilise pour une communicationn
extern void adresse_locale(char *local, int local_size, int *local_port, int communication);

#endif
