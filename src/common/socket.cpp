#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <pthread.h>

#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "socket.h"


volatile sig_atomic_t stop= 0;

// SERVEUR
// creer un point de connexion sur le port specifie 
int creer_point_connexion(int port)
{
	char localhost[128 +1];

	struct sockaddr_in adresse;
	struct hostent *host;

	int connexion;
	int listen_max= 4;
	int on;
	int code;


	//
	connexion= socket(PF_INET, SOCK_STREAM, 0);
	if(connexion < 0)
	{
		perror("point_connexion socket");
		return -1;
	}

	//
	#if 1
	on= 1;
	setsockopt(connexion, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	#endif

	//
	memset(&adresse, 0, sizeof(struct sockaddr_in));
	gethostname(localhost, 128);
	host= gethostbyname(localhost);
	if(host==NULL)
	{
		close(connexion);
		perror("point_connexion gethostbyname");
		return -1;
	}

	adresse.sin_family= host->h_addrtype;
	adresse.sin_port= htons(port);

	// printf("start\n");

	code= bind(connexion, (struct sockaddr *) &adresse, sizeof(struct sockaddr));
	if(code < 0)
	{
		close(connexion);
		perror("point_connexion bind");
		return -1;
	}

	//
	code= listen(connexion, listen_max);
	if(code < 0)
	{
		close(connexion);
		perror("point_connexion listen");
		return -1;
	}

	return connexion;
}


// 
int ouvrir_canal_communication(char *serveur, int port)
{
	struct sockaddr_in adresse;
	struct hostent *host;

	int communication;
	int code;

	//
	communication= socket(PF_INET, SOCK_STREAM, 0);
	if(communication < 0)
	{
		perror("canal_communication socket");
		return -1;
	}

	//
	memset(&adresse, 0, sizeof(struct sockaddr_in));
	host= gethostbyname(serveur);
	if(host==NULL)
	{
		close(communication);
		printf("canal_communication gethostbyname : serveur inconnu\n");
		return -1;
	}

	memcpy((char *) &adresse.sin_addr, host->h_addr, host->h_length);
	adresse.sin_family= host->h_addrtype;
	adresse.sin_port= htons(port);

	code= connect(communication, (struct sockaddr *) &adresse, sizeof(adresse));
	if(code < 0)
	{
		perror("canal_communication connect");
		return -1;
	}

	return communication;
}


// recupere l'adresse locale de la machine vue par le destinataire de la communication 'com'
void adresse_locale(char *local, int local_size, int *local_port, int com)
{
	struct hostent *host;
	struct sockaddr hostaddr;
	struct sockaddr_in *addr;
	unsigned int len;
	int code;
	
	
	len= sizeof(struct sockaddr);
	memset(&hostaddr, 0, sizeof(struct sockaddr));
	code= getsockname(com, &hostaddr, &len);
	if(code < 0)
	{
		perror("getsockname");
		exit(1);
	}
	
	if(hostaddr.sa_family!=AF_INET)
	{
		printf(" -- adresse non reconnue\n");
		exit(1);
	}

	addr= (struct sockaddr_in *) &hostaddr;
	host= gethostbyaddr((const char *) &addr->sin_addr, len, AF_INET);
	if(host==NULL)
	{
		perror("gethostbyaddr");
		exit(1);
	}

	if(local && local_size > 1)
	{
		strncpy(local, host->h_name, local_size);
		local[local_size -1]= 0;
	}

	if(local_port)
		*local_port= ntohs(addr->sin_port);
}

// recupere l'adresse de la machine distante (de l'autre cote de la socket) 
void adresse_client(char *client, int client_size, int *client_port, int com)
{
	struct sockaddr peeraddr;
	struct sockaddr_in *addr;
	struct hostent *host;
    unsigned int addr_size;
	int code;

	addr_size= sizeof(struct sockaddr);
	code= getpeername(com, &peeraddr, &addr_size);
	if(code < 0)
	{
		perror("adresse_client getpeername");
		exit(1);
	}
	
	if(peeraddr.sa_family!=AF_INET)
	{
		printf(" -- adresse non reconnue\n");
		exit(1);
	}

	addr= (struct sockaddr_in *) &peeraddr;
	host= gethostbyaddr((const char *) &addr->sin_addr, addr_size, PF_INET);
	if(host==NULL)
	{
		perror("adresse_client gethostbyaddr");
		exit(1);
	}

	if(client && client_size > 1)
	{
		strncpy(client, host->h_name, client_size);
		client[client_size -1]= 0;
	}

	if(client_port)
		*client_port= ntohs(addr->sin_port);
}

