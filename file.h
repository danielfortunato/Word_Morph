#ifndef fileHeader
#define fileHeader

#include "table.h"
#include "stdio.h"

char *LePalavra ( FILE * );
FILE *AbreFicheiro ( char *, char *);
char *CreateFile(char*);
void le_dic_aloca(st_dic *,char *,int[]);
void le_dicionario(st_dic *, char*);
void WriteFileSol(st_dic*,int[],int[],int,char*);
#endif
