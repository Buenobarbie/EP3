#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.c"
#include <string.h>

int main(){
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
        /*Pegando o caracter do arquivo */
        c = getc(fptr);

        /*Passando todas as letras maiusculas para minusculas */
        if('A'<= c && c <= 'Z')
            c += 32;
        
        /*Se o caracter não for uma letra, entao chegou ao fim de uma palavra */
        if(!('a' <= c && c <= 'z')){
            /*So sera realmente o fim de uma palavra se o caracter anterior for uma letra,
            ou seja ,se o tamanho da palavra nao for zero */
            if(sizePalavra!= 0){
                /*Armazenar a palavra */
                palavra = malloc(sizeof(char) * sizePalavra + 1);
                for(j = 0; j < sizePalavra; j++){
                    palavra[j] = auxPalavra[j];
                }
                palavra[j] = '\0';

                /*verificar se a palavra ja esta na arvore */
                aux = busca_arvore(raiz, palavra);

                /*Se nao estiver , adicionar */
                if(aux == NULL)
                    raiz = insere(raiz, palavra, sizePalavra);

                /*Se estiver , incrementar sua frequencia */
                else{
                    aux->freq++;

                    /*Atualizar a frequencia maxima do texto */
                    if(aux->freq > maxFreq)
                        maxFreq = aux->freq;
                free(palavra);
                }
            }
            sizePalavra = 0;
        }
        /*Caso nao seja o fim de uma palavra, incrementar o tamanho da palavra
        e armazenar o caracter na palavra auxiliar */
        else
            auxPalavra[sizePalavra++] = c;
        i++;
    }

    /*Criando o vetor de frequencias */
    celula ** frequencias = malloc(sizeof(celula *) * (maxFreq + 1));

    /*Passando por cada node da arvore e adiconando a palavra ao vetor de frequencias.
    Como eh inordem , as palavras serao colocadas em ordem alfabetica , 
    como estao dispostas na arvore */
    inordem(raiz, frequencias);

    while(k != 0){
    /*Recebendo o k menor  ou igual a frequencia maxima */
    printf("Digite um k (menor  ou igual a %d):", maxFreq );
    scanf("%d", &k);

    if(k > maxFreq)
        printf("Nao ha frequencias maiores que %d\n", maxFreq);

    /*Imprimindo as palavras com frequencia k */
    else
        imprimeListaRec(frequencias[k]);

    }

    for(i = 0; i < maxFreq + 1; i++){
        free(frequencias[i]);
    }
}