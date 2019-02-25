#include "heap.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Funçao que cria um bloco da heap*/
MinHeapNode* newMinHeapNode(int v, int dist)
{
    MinHeapNode* minHeapNode = ( MinHeapNode*) malloc(sizeof(MinHeapNode));
		if(minHeapNode==NULL)
		{
			printf("No memory allocation(minHeapNode)!!\n" );
			exit(-1);
		}
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

/*
*
*/

/*Função que cria a estrutura da heap*/
MinHeap* createMinHeap(int capacity)
{
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
		if(minHeap==NULL)
		{
			printf("No memory allocation(minHeap)!!\n" );
			exit(-1);
		}
    minHeap->pos = (int *)malloc(capacity *sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**) malloc(capacity * sizeof( MinHeapNode*));
    return minHeap;
}

/*
*
*/

/* Função que troca dois nos de modo a fazer o heapify*/
void swapMinHeapNode( MinHeapNode** a,  MinHeapNode** b)
{
  MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}


/*A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()*/
void minHeapify( MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1; /*son on the left*/
    right = 2 * idx + 2; /*son of the right*/

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;

    if (smallest != idx)
    {
        /* The nodes to be swapped in min heap*/
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        /* Swap positions*/
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        /* Swap nodes*/
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

/*A utility function to check if the given minHeap is ampty or not*/
int isEmpty( MinHeap* minHeap)
{
    return minHeap->size == 0;
}

/*Função que estrai o nó minimo da heap*/
 MinHeapNode* extractMin(MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    /* Store the root node*/
    MinHeapNode* root = minHeap->array[0];

    /* Replace root node with last node*/
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    /* Update position of last node*/
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    /* Reduce heap size and heapify root*/
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}


/*Function to decrease dist value of a given vertex v. This function
 uses pos[] of min heap to get the current index of node in min heap*/
void decreaseKey(MinHeap* minHeap, int v, int dist)
{
    /*Get the index of v in  heap array*/
    int i = minHeap->pos[v];

    /* Get the node and update its dist value*/
    minHeap->array[i]->dist = dist;

    /* Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop*/
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        /* Swap this node with its parent*/
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        /* move to parent index*/
        i = (i - 1) / 2;
    }
}

/*A utility function to check if a given vertex
// 'v' is in min heap or not*/
bool isInMinHeap( MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}

/*The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function*/
void dijkstra(Graph* graph, int src,st_dic*d,char*file_path,int mut)
{
	  LinkedList *pCrawl;
		pCrawl = createLinkedList();
		int v=0;
    int V = graph->N; /*Get the number of vertices in graph*/
    int dist[V];      /*Vetor com os valores das distancias a origem*/
    int parent[V];/*Vetor que vai obter o caminho*/
    /* minHeap represents set E*/
    MinHeap* minHeap = createMinHeap(V);

    /* Initialize min heap with all vertices. dist value of all vertices*/
    for ( v = 0; v < V; ++v)
    {
        parent[v]=-1;
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    /* Make dist value of src vertex as 0 so that it is extracted first*/

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    /* Initially size of min heap is equal to V*/
    minHeap->size = V;

    /* In the followin loop, min heap contains all nodes
       whose shortest distance is not yet finalized.*/
    while (!isEmpty(minHeap))
    {
        /* Extract the vertex with minimum distance value*/
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; /* Store the extracted vertex number*/


        /* Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values*/

   			pCrawl = graph->adjLst[u];

        while (pCrawl != NULL)
        {

						v=getdestLinkedList(pCrawl);

            /*If shortest distance to v is not finalized yet, and distance to v
             through u is less than its previously calculated distance*/
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && (getWeightLinkedList(pCrawl) + dist[u] < dist[v])&&getWeightLinkedList(pCrawl)<=pow(mut,2))
            {
                dist[v] = dist[u] + getWeightLinkedList(pCrawl);
                /* update distance value in min heap also*/
                parent[v]=u;
                decreaseKey(minHeap, v, dist[v]);
                if(u==d->ind_p2)
                  break;

            }
            if(u==d->ind_p2)
              break;


						if(getnextLinkedList(pCrawl) == NULL)
							break;

						pCrawl = getNextNodeLinkedList(pCrawl);

        }

    }

  /*Imrpime o ficheiro com as soluções*/
    WriteFileSol(d,parent,dist,d->ind_p2,file_path);

}
/*Função que vai imprimir no ficheiro as soluções*/
void printPath(char*filename,int parent[], int j,st_dic*d,int dist[])
{
  FILE*f;
  if(dist[d->ind_p2]==999999)
  {
      f=fopen(filename,"a");
      fprintf(f,"%s", d->matriz[d->tamanho_palavra][d->ind_p1]);
      fprintf(f," -1\n");
      fprintf(f,"%s\n\n", d->matriz[d->tamanho_palavra][d->ind_p2]);
      fclose(f);
      return;
  }

  if (parent[j]==-1)
  {
    f=fopen(filename,"a");
    fprintf(f,"%s", d->matriz[d->tamanho_palavra][j]);
    fprintf(f," %d\n",dist[d->ind_p2]);
    fclose(f);
    return;
  }

  printPath(filename, parent,parent[j],d,dist);
  f=fopen(filename,"a");
  fprintf(f,"%s\n", d->matriz[d->tamanho_palavra][j]);
  fclose(f);
  return;
}
