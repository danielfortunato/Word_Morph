#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph.h"
#include "file.h"
#include "defs.h"
#include "LinkedList.h"

/******************************************************************************
*Função que cria uma aresta do grafo.
*
*
*
 *****************************************************************************/
Edge *createEdge(int dest, int w){

	Edge *e_ptr;

	e_ptr = (Edge*) malloc(sizeof(Edge));
	if(e_ptr == NULL ){
		printf("No memory to allocate Edge!");
		exit(-1);
	}
	e_ptr->dest = dest;
	e_ptr->w    = w ;
	return e_ptr;
}
/******************************************************************************
*Função que destroi a aresta do grafo.
*
*
*
 *****************************************************************************/
void destroyEdge( Item item ){
	free((Edge*)item);
}
/******************************************************************************
*Função que vai destruir o grafo libertando toda a memoria que foi alocada
*para o criar.
*
*
 *****************************************************************************/
void destroyGraph( Graph* graph_ptr ){
	int i;
	for( i = 0; i < graph_ptr->N; i++ ){
		freeLinkedList( graph_ptr->adjLst[i], &destroyEdge);
	}
	free(graph_ptr->adjLst);
	free(graph_ptr);
}
/******************************************************************************
*Função que aloca a memória para a estrutura do grafo.
*
*
*
 *****************************************************************************/
Graph* createGraph( int N ){
	Graph* graph_ptr;
	int i=0;

	graph_ptr = (Graph*)malloc( sizeof(Graph));
	if( graph_ptr == NULL ){
		printf("No memory for graph allocation!");
		exit(0);
	}

	graph_ptr->N = N;
	graph_ptr->adjLst = (LinkedList**)malloc(sizeof(LinkedList*)*N);
	for(i = 0; i < N;i++ )
	{
		graph_ptr->adjLst[i] = NULL;
	}
	return graph_ptr;
}

/******************************************************************************
*Função que adiciona arestas ao grafo de forma não ordenada.
*
*
*
 *****************************************************************************/
void addEdgesToGraph( Graph* graph_ptr, int i, int j, int w )
{
	graph_ptr->adjLst[i] = insertUnsortedLinkedList(graph_ptr->adjLst[i],createEdge(j, w));
	graph_ptr->adjLst[j] = insertUnsortedLinkedList(graph_ptr->adjLst[j],createEdge(i, w));
}
/******************************************************************************
*Função que vai preencher o grafo com os dados recolhidos da tabela de palavras
*e com as mutações indicadas no ficheiro de problemas.
*
*
 *****************************************************************************/
Graph* fillGraph( st_dic*d,int mut[],int tam_pal)
{
	int val=0;
  int i, j;
	int r=0;
	Graph* graph_ptr;
	char**table;

	table=d->matriz[tam_pal];
	r=d->ocorr[tam_pal];
	graph_ptr=createGraph(r);

	for(i=0;i<r;i++)
	{
		for(j=i+1;j<r;j++)
		{
				val=calculateWeight(table[i],table[j],d,mut[tam_pal]);/*Calcula o peso da aresta*/

				if(val>0)
				{
					addEdgesToGraph( graph_ptr, i, j, val);/*Adiciona a aresta*/
				}
		}
	}

	return graph_ptr;
}
/******************************************************************************
*Função que calcula o peso da aresta, comparando letra a letra as duas palavras.
*
*
*
 *****************************************************************************/
int calculateWeight(char*word1,char*word2,st_dic*d,int mut)
{
	int i=0;
	int weight=0;

while(word1[i]!='\0')
	{
		if(word1[i]!=word2[i])
		{
			weight++;

			if(weight>mut)
				return 0;
		}
		i++;
	}

	return weight*weight;
}
