#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.c"


int main(){
    //Armazenando as palavras e o tamanho
    FILE * fptr;
    fptr = fopen("example.txt","r");
    char c = 'a';
    int sizePalavra = 0;
    int i = 0, j = 0;
    int k = 1;
    int maxFreq = 1;
    char *palavra;
    char auxPalavra[100];
    node * raiz;
    node * aux;

    while(c != EOF){
        c = getc(fptr);
        if('A'<= c && c <= 'Z')
            c += 32;
        if(!('a' <= c && c <= 'z')){
            if(sizePalavra!= 0){
                palavra = malloc(sizeof(char) * sizePalavra + 1);
                for(j = 0; j < sizePalavra; j++){
                    palavra[j] = auxPalavra[j];
                }
                palavra[j] = '\0';
                aux = busca_arvore(raiz, palavra);
                if(aux == NULL)
                    raiz = insere(raiz, palavra, sizePalavra);
                else{
                    aux->freq++;
                    if(aux->freq > maxFreq)
                        maxFreq = aux->freq;
                }
            }
            sizePalavra = 0;
        }
        else
            auxPalavra[sizePalavra++] = c;
        i++;
    }
    celula ** frequencias = malloc(sizeof(celula *) * (maxFreq + 1));

    inordem(raiz, frequencias);
    while(k != 0){
    printf("Digite um k (menor  ou igual a %d):", maxFreq + 1);
    scanf("%d", &k);
    imprimeListaRec(frequencias[k]);

    }
}