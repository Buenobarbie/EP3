#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.c"

celula * frequencias[100];

int main(){
    //Armazenando as palavras e o tamanho
    char text[100] = "Algoritmos por divisao e conquista tem passos em casa nivel da recursao";
    char c = '0';
    int iniPalavra = 0;
    int sizePalavra = 0;
    int i = 0, j = 0;
    int k = 1;
    char *palavra;
    node * raiz;
    node * aux;

    while(c){
        if('A'<= text[i] && text[i] <= 'Z')
            text[i] += 32;
        c = text[i];
        //printf("%c", c);
        if(!('a' <= c && c <= 'z')){
            if(sizePalavra!= 0){
                palavra = malloc(sizeof(char) * sizePalavra + 1);
                for(j = 0; j < sizePalavra; j++, iniPalavra++){
                    palavra[j] = text[iniPalavra];
                }
                palavra[j] = '\0';
                aux = busca_arvore(raiz, palavra);
                if(aux == NULL)
                    raiz = insere(raiz, palavra, sizePalavra);
                else
                    aux->freq++;
                
            }
            iniPalavra = i+1;
            sizePalavra = 0;
        }
        else
            sizePalavra++;
        i++;
    }
    inordem(raiz, frequencias);
    while(k != 0){
    printf("Frequencias :");
    scanf("%d", &k);
    imprimeListaRec(frequencias[k]);

    }
}