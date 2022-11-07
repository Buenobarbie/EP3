#include <stdio.h>
#include <stdlib.h>
#define item char *
#define igual 1
#define maior 2
#define menor 3

//Binary Search Tree setup
typedef struct cel_arvore {
  item info; 
  int size;
  int freq;
  struct cel_arvore * esq; 
  struct cel_arvore * dir;
} node; 



//Linked list setup
typedef struct cel{
    item info;
    struct cel *prox;
} celula;

int comparaPalavras(char * palavra1, char * palavra2);
node * busca_arvore (node * raiz, item x);
node * insere (node * raiz, item x, int size);
void inordem(node * raiz,celula * freq[100]);

celula * insereNoFim(celula * inicio, item x);
void imprimeListaRec(celula * inicio);
void imprimePalavra(char * palavra);

//Binary Search Tree functions

int comparaPalavras(char * palavra1, char * palavra2){
  int i = 0;
  while(palavra1[i] && palavra2[i]){
    if(palavra1[i] > palavra2[i])
      return maior;
    if(palavra1[i] < palavra2[i])
      return menor;
    i++;
  }
  if(palavra1[i] == palavra2[i])
    return igual;
  if(palavra1[i] == '\0')
    return menor;
  return maior;
}

node * busca_arvore (node * raiz, item x){
  if (raiz == NULL) return NULL;
  if (comparaPalavras(raiz->info, x) == igual) return raiz; 
  if (comparaPalavras(raiz->info, x) == menor)
    return busca_arvore (raiz->dir, x);
  return busca_arvore (raiz->esq, x);
}

node * insere (node * raiz, item x, int size){
  if (raiz == NULL){
    raiz = malloc(sizeof (node));
    raiz->info = x;
    raiz->size = size;
    raiz->freq = 1;
    raiz->esq = raiz->dir = NULL;
    return raiz; 
  }
  if (comparaPalavras(raiz->info, x) == igual)
    return raiz; 
  if (comparaPalavras(raiz->info, x) == menor)
    raiz->dir = insere (raiz->dir, x, size);
  else 
    raiz->esq = insere (raiz->esq, x, size);
  return raiz; 
}

void inordem(node * raiz, celula * freq[100]){
  if (raiz != NULL){
    inordem(raiz->esq,freq);
    printf("%d", raiz->freq);
    imprimePalavra(raiz->info);
    freq[raiz->freq] = insereNoFim(freq[raiz->freq], raiz->info);
    inordem(raiz->dir,freq);
  }
}


//Linked List functions

celula * insereNoFim(celula * inicio, item x){
    celula * aux = malloc(sizeof(celula));
    aux->info = x;
    aux->prox = NULL;
    celula * p, *ant;
    for(ant = NULL, p = inicio; p != NULL; ant = p, p = p-> prox );
    if(inicio != NULL) ant->prox = aux;
    else inicio = aux;
        
    return inicio;

}

void imprimeListaRec(celula * inicio){
    if(inicio != NULL){
        imprimePalavra(inicio->info);
        imprimeListaRec(inicio->prox);
    }
    else
        printf("\n");
}

void imprimePalavra(char * palavra){
    for(int i = 0; palavra[i]; i++)
        printf("%c", palavra[i]);
    printf("\n");
}

