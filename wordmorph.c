#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "table.h"
#include "file.h"
#include "graph.h"
#include "LinkedList.h"
#include "defs.h"
#include "heap.h"

int main ( int argc, char **argv )
{
  st_dic dic;
  Graph* grafo[TAM_MAX];
	int tipo_grafo[TAM_MAX]={0};
	int mutacoes[TAM_MAX]={0};
  FILE *f_in = NULL;
  FILE *f_1 = NULL;
  char*file_path=NULL;
  int i=0;

  if ( argc < 3 ) /*Tratamento de erros*/
  {
    fprintf ( stderr, "ERROR: missing filename in argument!\n" );
    exit ( 6 );
  }

  file_path=CreateFile(argv[2]);/*Cria o ficheiro do camiho*/
	f_in = fopen(argv[2], "r" );

  /*Le o ficheiro de problemas uma primeira vez para ver o total de grafos diferentes
  e o numero maximo de mutações existentes para cada tipo de grafo*/
	while(fscanf(f_in, "%s %s %d", dic.palavra_1, dic.palavra_2,&dic.mut_max)!=EOF)
	{
		dic.tamanho_palavra=strlen(dic.palavra_2);
    if(calculateWeight(dic.palavra_2,dic.palavra_1,&dic,dic.mut_max)!=0||calculateWeight(dic.palavra_2,dic.palavra_1,&dic,dic.mut_max)!=1)
    {
  		tipo_grafo[dic.tamanho_palavra]=1;
  		mutacoes[dic.tamanho_palavra]=dic.mut_max;
    }
	}

	  le_dicionario(&dic,argv[1]);
	  AlocaTabelaPalavras(&dic,tipo_grafo);
	  le_dic_aloca(&dic,argv[1],tipo_grafo);

	  for( i=0; i < TAM_MAX; i++)
	  {
	    if(dic.ocorr[i]!=0)
	    	qsort(dic.matriz[i],dic.ocorr[i],sizeof(char*),compareStrings);/*Ordena a tabela de palavras*/
	  }

		for(i=0;i<TAM_MAX;i++)
		{
			if(tipo_grafo[i]==1)
			{
				grafo[i]=fillGraph(&dic,mutacoes,i);/*Preenche os grafos necessários*/
			}
		}
		rewind(f_in);
		while(fscanf(f_in, "%s %s %d", dic.palavra_1, dic.palavra_2,&dic.mut_max)!=EOF)
		{
			dic.tamanho_palavra=strlen(dic.palavra_2);
			dic.ind_p1=procura_palavra(dic.palavra_1,&dic);
			dic.ind_p2=procura_palavra(dic.palavra_2,&dic);
    	if(dic.ind_p1==dic.ind_p2||calculateWeight(dic.palavra_2,dic.palavra_1,&dic,dic.mut_max)==1)/*Se apenas existir diferença de uma letra ou nao existir diferença*/
      {                                                                                           /*não necessita de criar grafo e escreve logo no ficheiro*/
        f_1=fopen(file_path,"a");
        if(calculateWeight(dic.palavra_2,dic.palavra_1,&dic,dic.mut_max)==1)fprintf(f_1, "%s 1\n%s\n\n",dic.palavra_1,dic.palavra_2);
        else fprintf(f_1, "%s 0\n%s\n\n",dic.palavra_1,dic.palavra_2);
        fclose(f_1);
        continue;
      }
     		dijkstra(grafo[dic.tamanho_palavra],dic.ind_p1,&dic,file_path,dic.mut_max);/*Realiza o algoritmo de procura de caminho*/
		}

/*A partir daqui liberta toda a memoria alocada*/
	for(i=0;i<TAM_MAX;i++)
	{
		if(tipo_grafo[i]==1)
			destroyGraph(grafo[i]);
	}
  fclose(f_in);
  free_mat(&dic,tipo_grafo);
  free(file_path);
  return (0);
}
