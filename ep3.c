#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.c"


int main(){
    //Armazenando as palavras e o tamanho
    char text[100] = "Algoritmos por divisao e conquista tem passos em casa nivel da recursao";
    char c = '0';
    int iniPalavra = 0;
    int sizePalavra = 0;
    int i = 0, j = 0;
    int k = 1;
    int maxFreq = 1;
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
                else{
                    aux->freq++;
                    if(aux->freq > maxFreq)
                        maxFreq = aux->freq;
                }
            }
            iniPalavra = i+1;
            sizePalavra = 0;
        }
        else
            sizePalavra++;
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