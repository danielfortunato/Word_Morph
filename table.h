#ifndef tableHeader
#define tableHeader

#define TAM_MAX 30
#define MAX_STR 50
typedef struct _st_dic{
    int mut_max;/*Número maximo de mutações permitidas para o problema*/
    int tamanho_palavra;/*tamanho das palavras*/
    char palavra_1[50];
    char palavra_2[50];
    int ind_p1;/*Indice na tabela da primeira palavra do problema*/
    int ind_p2;/*Indice na tabela da segunda palavra do problema*/
    char*** matriz;/*Tabela de palavras*/
    int ocorr[TAM_MAX];/*Vetor de inteiros com o numero de ocorrencias de cada palavra no dicionario*/
}st_dic;

void AlocaTabelaPalavras ( st_dic *,int[]);
int procura_palavra(char*,st_dic *);
int compareStrings(const void *, const void *);
void conta_palavras(st_dic*,char *);
void free_mat(st_dic*,int[]);
#endif
