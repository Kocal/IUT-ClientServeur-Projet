#ifndef _CAUSE_H
#define _CAUSE_H


typedef struct
{
	int com_lire;
	int com_ecrire;
} CAUSE_PARAM;

extern void *cause(void *voidparam);


#endif

