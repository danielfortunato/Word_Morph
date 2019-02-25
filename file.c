#include "file.h"
#include "table.h"
#include "heap.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

/******************************************************************************
 * LePalavra()
 *
 * Arguments: f - pointer to file where word will be read
 * Returns: pointer to word just read
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

char *LePalavra ( FILE * f )
{
  static char palavra[MAX_STR];
  /* It is assumed that the words present in the text files do not exceed
     100 characters in length  */
  /* Note that the variable palavra is declared as "static". */
  if ( fscanf ( f, "%s", palavra ) ==1 )
    return (palavra);
  else
    return ((char *) NULL);
}

/******************************************************************************
 * AbreFicheiro()
 *
 * Arguments: nome - pointer to string holding name of file to open
 *            mode - pointer to string holding mode to use for opening file
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *
 *****************************************************************************/

FILE *AbreFicheiro ( char *nome, char *mode )
{
  FILE *f=NULL;
  f = fopen ( nome, mode );
  if ( f == NULL ) {
    fprintf ( stderr, "ERROR: It is not possible to open file %s!\n", nome );
    exit ( 1 );
    /* Error messages are sent to the stderr channel.
       Use an exit number different from 0 (zero) in case of error.*/
  }
  return (f);
}
/******************************************************************************
*Função que cria o ficheiro onde vão ser representados os caminhos.
*
*
*
 *****************************************************************************/
char* CreateFile(char *ficheiro)
{
  FILE*f=NULL;
  char *nome;
  int i=0;
  nome = (char *) malloc((strlen(ficheiro)+2)*sizeof(char)) /* -- Insert code for memory allocation,  remember to add space for the dot (.), the filename extension and the string termination --*/ ;
  if ( nome == NULL ) {
    fprintf ( stderr, "ERROr: not enough memory available!\n" );
    exit ( 5 );
  }
  strcpy ( nome, ficheiro );
  i=strlen(nome);
  nome[i]='h';
  nome[i-1]='t';
  nome[i-2]='a';
  nome[i-3]='p';
  f=fopen(nome,"w");
  fclose(f);
  return nome;
}

/****************************************************************************
*Função que regista quantas palavras existem de cada tamanho para a alocação da
*tabeçla de palavras.
*
*
******************************************************************************/
void le_dicionario(st_dic *d, char*ficheiro)
{
  FILE * f=NULL;
  char*palavra;
  int i=0;
  f = AbreFicheiro(ficheiro,"r");

  for(i=0;i<TAM_MAX;i++)
  {
    d->ocorr[i]=0;
  }

  while ( ( palavra = LePalavra ( f ) ) != NULL)
  {
    d->ocorr[strlen(palavra)]++;
  }
fclose(f);
}
/****************************************************************************
*Função que vai lendo o dicionario e colocando as palavras na tabela de palavras.
*
*
*
******************************************************************************/
void le_dic_aloca(st_dic *d,char *ficheiro,int tipo_grafo[])
{
  FILE *f =NULL;
  char*palavra;
  int i;
  f= AbreFicheiro(ficheiro,"r");

  for(i=0;i<TAM_MAX;i++)
  {
    d->ocorr[i]=0;
  }

  while ( ( palavra = LePalavra ( f ) ) != NULL)
  {
    if(tipo_grafo[strlen(palavra)]==1)
    {
      strcpy(d->matriz[strlen(palavra)][(d->ocorr[strlen(palavra)])],palavra);
      d->ocorr[strlen(palavra)]++;
    }
  }

  fclose(f);
}
/****************************************************************************
*Função que escreve o ficheiro com as soluções, ou seja, os caminhos entre
*palavras.
*
*
******************************************************************************/
void WriteFileSol(st_dic*d,int parent[],int dist[],int j,char*file_path)
{
  FILE*f1=NULL;
  printPath(file_path,parent,d->ind_p2,d,dist);
  f1=fopen(file_path,"a");
  fprintf(f1, "\n" );
  fclose(f1);
}
