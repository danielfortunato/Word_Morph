#include "table.h"
#include "file.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
/*Função que vai alocar a tabela de palavras conforme as necessidades do utilizador*/
void AlocaTabelaPalavras ( st_dic *d,int tipo_grafo[])
{
  int i,j;
  d->matriz =  (char ***) malloc(TAM_MAX*sizeof(char **));

  if ( d->matriz== NULL )
   {
    fprintf ( stderr, "ERROR: not enough memory available!\n" );
    exit ( 2 );
   }

  for(j=0;j<TAM_MAX;j++)
  {
    if(tipo_grafo[j]==1)
    {
      d->matriz[j]= (char**)malloc((d->ocorr[j])*sizeof(char*));

      if ( d->matriz[j]== NULL )
       {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 2 );
       }

       for(i=0;i<d->ocorr[j];i++)
       {
           d->matriz[j][i]= (char*)malloc((j+1)*sizeof(char));
           if ( d->matriz[j][i]== NULL )
            {
             fprintf ( stderr, "ERROR: not enough memory available!\n" );
             exit ( 2 );
            }
      }
    }
 }

}

/****************************************************************************
* Função que vai realizar a procura de uma palavra na tabela de palavras
* utilzando o algoritmo da procura binaria. Esta vai retornar um inteiro
* com o indice da posição onde se encontra a palavra desejada.
*
******************************************************************************/
int procura_palavra(char*palavra,st_dic *d)
{
  int first, last, middle,n;
  n=d->ocorr[strlen(palavra)];
  first = 0;
  last = n ;
  middle = (first+last)/2;

   while (first <= last)
   {
     if (strcmp(d->matriz[d->tamanho_palavra][middle],palavra)==0)
     {
      return middle;
     }
      else if (strcmp(d->matriz[d->tamanho_palavra][middle],palavra)<0)
         first = middle;
       else if (strcmp(d->matriz[d->tamanho_palavra][middle],palavra)>0)
         last = middle;

      middle = (first + last)/2;

   }

   return -1;
}

/****************************************************************************
*Função que compara duas palavras, esta é utilizada essencialmente na função
*qsort.
*
*
******************************************************************************/
int compareStrings(const void *stackA, const void *stackB)
{
  const char *a=*(const char**)stackA;
  const char *b=*(const char**)stackB;
  return strcmp(a,b);
}
/****************************************************************************
* Função utilizada para libertar a memória alocada para a criação da tabela
* de palavras.
*
*
******************************************************************************/
void free_mat(st_dic*d,int tipo_grafo[])
{
  int i,j;

    for(i=0;i<TAM_MAX;i++)
    {
      if(tipo_grafo[i]==1)
      {
      for(j=0;j<d->ocorr[i];j++)
        free(d->matriz[i][j]);

      free(d->matriz[i]);
      }
    }
    free(d->matriz);
}
