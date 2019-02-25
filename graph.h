#ifndef graphHeader
#define graphHeader

#include "defs.h"
#include "table.h"
#include "LinkedList.h"
#include <stdbool.h>
#include <math.h>


typedef struct _graph{
	int N; /*Tamanho do grafo*/
	LinkedList **adjLst;  /*Lista de adjacencias do grafo*/ 
}Graph;

Edge* createEdge(int, int );
void destroyEdge( Item );
void destroyGraph( Graph* );
Graph* createGraph( int );
void addEdgesToGraph( Graph* , int , int , int );
Graph* fillGraph( st_dic*,int[],int );
int calculateWeight(char*,char*,st_dic*,int);

#endif
