/*
 *  File name: LinkedList.c
 *
 *  Author: 2013 Fall Semester AED Team
 *
 *  Release date: 2013/10/04
 *
 *  Description: C-Implementation of an Abstract Linked List
 *
 *  Implementation details:
 *    Linked list node: Each node of the list contains a pointer to
 *   the item stored in the node and a pointer to the next node. The
 *   item is specified in the file defs.h.
 *
 *  Version: 1.0
 *
 *  Change log: N/A
 *
 */



/* Header Inclusions                                              */
#include<stdio.h>
#include<stdlib.h>



/* Include Header File with Data Type and Function Prototypes     */
#include"LinkedList.h"



/*
 *  Data Type: LinkedListStruct
 *
 *  Description: Structure with:
 *                 1) Pointer to the item of the linked list node
 *                 2) Pointer to next node of the linked list.
 */
struct LinkedListStruct
{
  Item this;
  LinkedList * next;
};



/*
 *  Function:
 *    initLinkedList
 *
 *  Description:
 *    Initializes a new linked list.
 *
 *  Arguments:
 *    None
 *
 *  Return value:
 *    Returns the pointer to a new linked list.
 */
LinkedList * initLinkedList(void)
{
  return NULL;
}



/*
 *  Function:
 *    freeLinkedList
 *
 *  Description:
 *    Frees the memory allocated to a linked list.
 *
 *  Arguments:
 *    Pointer to the first element of a linked list:
 *      (LinkedList *) first
 *    Function to free the memory allocated to the items:
 *      void freeItem(Item)
 *
 *  Return value:
 *    None
 */
void freeLinkedList(LinkedList * first, void (* freeItemFnt)(Item))
{
  LinkedList * next;
  LinkedList * aux;

  /* Cycle from the first to the last element                     */
  for(aux = first; aux != NULL; aux = next)
  {
    /* Keep trace of the next node                                */
    next = aux->next;

    /* Free current item                                          */
/*    freeItemFnt(aux->this);*/
free(aux->this);

    /* Free current node                                          */
    free(aux);
  }

  return;
}

/*
 *  Function:
 *    getNextNodeLinkedList
 *
 *  Description:
 *    Returns the next node of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the next node of a linked list. NULL
 *   is returned in case the current node is empty or there is no
 *   node following the current node.
 */
LinkedList * getNextNodeLinkedList(LinkedList * node)
{
  return ((node == NULL) ? NULL : node->next);
}

/******************************************************************************
*Função que cria uma LinkedList
*
*
*
 *****************************************************************************/
LinkedList* createLinkedList()
{
  LinkedList*new;
  new = (LinkedList*)malloc(sizeof(LinkedList));
  return new;
}
/******************************************************************************
*Função que devolve o peso do vertice do grafo.
*
*
*
 *****************************************************************************/
int getWeightLinkedList(LinkedList*node)
{
  return node->this->w;
}
/******************************************************************************
*Função que devolve o vertice de destino.
*
*
*
 *****************************************************************************/
int getdestLinkedList(LinkedList*node)
{
  return node->this->dest;
}
/******************************************************************************
*Função que retorna o nó seguinte da lista.
*
*
*
 *****************************************************************************/
LinkedList* getnextLinkedList(LinkedList*node)
{
  return node->next;
}

/*
 *  Function:
 *    insertUnsortedLinkedList
 *
 *  Description:
 *    Creates a new linked list node.
 *
 *  Arguments:
 *    Item to associate to the new node:
 *      Item this
 *    Pointer to the next node:
 *      (LinkedList *) next
 *
 *  Return value:
 *    Returns the pointer to the node.
 */
LinkedList * insertUnsortedLinkedList(LinkedList * next, Item this)
{
  LinkedList * new;

  /* Memory allocation                                            */
  new = (LinkedList *) malloc(sizeof(LinkedList));

  /* Check memory allocation errors                               */
  if(new == NULL)
  {
    return NULL;
  }
  /* Initialize new node                                          */
  new->this = this;
  new->next = next;

  return new;
}
