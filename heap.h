#ifndef HeapHeader
#define HeapHeader

#include "defs.h"
#include "table.h"
#include "LinkedList.h"
#include "graph.h"
#include <stdbool.h>
#define INT_MAX 999999

/*Structure to represent a min heap node*/
typedef struct {
    int  v;
    int dist;
}MinHeapNode;

/*Structure to represent a min heap*/
typedef struct {
    int size;      /* Number of heap nodes present currently*/
    int capacity;  /* Capacity of min heap*/
    int *pos;     /* This is needed for decreaseKey()*/
    MinHeapNode **array;
}MinHeap;

void FixUp(MinHeap* , int );
void FixDown(MinHeap* ,int , int);
MinHeapNode* newMinHeapNode(int , int );
MinHeap* createMinHeap(int );
void swapMinHeapNode( MinHeapNode** , MinHeapNode** );
void minHeapify( MinHeap* , int );
int isEmpty( MinHeap* );
MinHeapNode* extractMin( MinHeap* );
void decreaseKey( MinHeap* , int , int );
bool isInMinHeap( MinHeap *, int );
void printArr(int[] , int );
void dijkstra(Graph* , int , st_dic*,char*,int);
void printPath(char*,int[], int,st_dic*,int[] );


#endif
