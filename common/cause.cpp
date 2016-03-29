/*
	TP 2 Client serveur
	
	partie commune : echange d'un message entre 2 descripteur de fichiers
	
	mailto:jciehl@bat710.univ-lyon1.fr
 */

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "cause.h"


void *cause(void *voidparam)
{
	CAUSE_PARAM *param= (CAUSE_PARAM *) voidparam;
	char msg;
	int code;
	
	for(;;)
	{
        code = read(param->com_lire, &msg, 1);
		if(code <= 0)
			break;

        code = write(param->com_ecrire, &msg, 1);
		if(code <= 0)
			break;
	}

	pthread_exit(NULL);
	return NULL;
}

