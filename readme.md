
# Relatório EP3

- Nome : Bárbara Bueno

- NUSP : 13679530


## 1) dataStructures.c
Arquivo com as funções das estruturas de dados utilizadas.

### 1.1) Árvore de Busca Binária
Utilizada para armazenar as palavras em ordem
alfabética e otimizar a busca por palavras 
já analisadas no texto.

#### 1.1.1) Estrutura (node)

```c
typedef struct cel_arvore {
  item info; 
  int freq;
  struct cel_arvore * esq; 
  struct cel_arvore * dir;
} node; 
```

- info (char *) : ponteiro para o vetor de caracteres com a palavra armazenada;
- freq : frequência da palavra no texto;
- esq e dir : ponteiros para os nodes esquerdo e direito da árvore , respectivamente;


#### 1.1.2) Função busca_arvore
Procura a palavra **x** na árvore, de acordo com a
distribuição alfabética das palavras, utilizando 
a função comparaPalavras(). Assim, caso encontre a 
palavra, retorna um ponteiro para o node em que se encontra. Caso contrário,
ou seja , caso chegue a um node vazio, significa que não achou e
 retorna NULL.
```c
node * busca_arvore (node * raiz, item x){
  if (raiz == NULL) return NULL;
  if (comparaPalavras(raiz->info, x) == igual) 
    return raiz; 
  if (comparaPalavras(raiz->info, x) == menor) 
    return busca_arvore (raiz->dir, x);
  return busca_arvore (raiz->esq, x);
}
```

#### 1.1.3) Função insere
Insere a palavra **x** na árvore binária,. Ela
percorre a ávore binária , utilizando a função
comparaPalavras() e chamando recursivamente a função insere(), de forma a encontrar o lugar correto 
para inserir e manter a ávore em ordem alfabética.
Retorna um ponteiro para o node criado.


```c
node * insere (node * raiz, item x){
  if (raiz == NULL){
    raiz = malloc(sizeof (node));
    raiz->info = x;
    raiz->freq = 1;
    raiz->esq = raiz->dir = NULL;
    return raiz; 
  }
  if (comparaPalavras(raiz->info, x) == igual)
    return raiz; 
  if (comparaPalavras(raiz->info, x) == menor)
    raiz->dir = insere (raiz->dir, x);
  else 
    raiz->esq = insere (raiz->esq, x);
  return raiz; 
}
```
#### 1.1.4) Função inordem
Passa por cada um dos nodes da ávore binária ,
em ordem alfabética,
e o adiciona no fim da lista ligada da posição de frequência
correspondente no vetor freq.
```c
void inordem(node * raiz, celula * freq[]){
  if (raiz != NULL){
    inordem(raiz->esq,freq);
    freq[raiz->freq] = insereNoFim(freq[raiz->freq], raiz->info);
    inordem(raiz->dir,freq);
  }
}

```




### 1.2) Lista Ligada
Utilizada para armazenar as palavras em ordem
alfabética de acordo com a frequência.

#### 1.2.1) Estrutura (celula)

```c
typedef struct cel{
    item info;
    struct cel *prox;
} celula;
```

- info (char *) : ponteiro para o vetor de caracteres com a palavra armazenada;
- prox : ponteiro para a próxima célula da lista ligada;



#### 1.2.2) Função insereNoFim
Insere a palavra **x** no final da lista ligada. Cria uma nova célula e,
a partir do inicio fornecido, percorre a lista
até achar uma celula que aponta para NULL, inserindo
a informação na posição seguinte. Retorna o inicio.

```c
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
```
#### 1.2.3) Função imprimeListaRec
Imprime as palavras da lista utiliando recursão.
Enquanto a celula não for vazia, imprime a sua informação.
```c
void imprimeListaRec(celula * inicio){
    if(inicio != NULL){
        imprimePalavra(inicio->info);
        imprimeListaRec(inicio->prox);
    }
    else
        printf("\n");
}
```

### 1.3) Outras funções

#### 1.3.1) Função imprimePalavra
Imprime uma palavra a partir do ponteiro para o início do vetor de char.
Imprime o caracter enquanto ele for diferente de '\0'.
```c
void imprimePalavra(char * palavra){
    for(int i = 0; palavra[i]; i++)
        printf("%c", palavra[i]);
    printf("\n");
}
```

#### 1.3.2) Função comparaPalavras
Veriifcar se uma palavra vem alfabeticamente antes ou depois que outra,
ou se são iguais. Como todas as letras são minúsculas,
basta usar os comparadores > e < entre os caracteres de cada palavra.
Caso a função não tenha retornado e saiu do loop while, significa que uma ou ambas
as palavras já tiveram todos os caracteres comparados (chegou no '\0') e, assim, 
a palavra de menor tamanho será a menor alfabeticamente.
```c
int comparaPalavras(char * palavra1, char * palavra2){
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
```

## 2) Código principal (ep3.c)

Arquivo principal, onde é setado o nome
do arquivo de texto a ser lido
e recebe os Ks para imprimir a lista de palavras
com frequência correspondente.

### 2.1) Lendo arquivo
Utilizando a função fopen() , abre-se
o arquivo "example.txt" no modo leitura ("r").
No loop principal, enquanto houver caracter do 
arquivo para ser lido ( c diferente de EOF (end of file / fim do arquivo)),
utiliza-se a função getc(fptr) para pegar o
próximo caracter do arquivo.

```c
    FILE * fptr;
    fptr = fopen("example.txt","r");
    char c = 'a';

    while(c != EOF){
        c = getc(fptr);
        /* code */
    }
```

### 2.2) Letras maiúsculas
Passando todas as letras maiúsculas para minúsculas
para facilitar a comparação alfabética .

```c
    if('A'<= c && c <= 'Z')
        c += 32;
```

### 2.3) Armazenando as palavras

- Se o caracter não for uma letra e o tamanho da  palavra for maior que zero , significa que chegou ao fim da palavra e pode armazená-la. Para isso , aloca-se dinamicamente um espaço de memória para a palavra, utilizando o tamanho da palavra contabilizado, e transcrevem-se os caracteres da palavra auxiliar para a variável palavra , adicionando um '\0' ao final.
```c
if(!('a' <= c && c <= 'z')){
            if(sizePalavra!= 0){
                /*Armazenar a palavra */
                palavra = malloc(sizeof(char) * sizePalavra + 1);
                for(j = 0; j < sizePalavra; j++){
                    palavra[j] = auxPalavra[j];
                }
                palavra[j] = '\0';
```
- Verifica se a palavra já está na árvore e armazena em um node auxiliar.
```c
                aux = busca_arvore(raiz, palavra);
```
- Caso o aux seja NULL, significa que a palavra ainda não foi adicionada , então a inserimos na árvore , atualizando a raiz.
```c
                if(aux == NULL)
                    raiz = insere(raiz, palavra, sizePalavra);
```
- Caso o aux não seja NULL , a palavra já foi adicionada na árvore e é necessário atualizar sua frequência. Além disso, a frequência máxima no texto é atualizada.
```c
                else{
                    aux->freq++;

                    if(aux->freq > maxFreq)
                        maxFreq = aux->freq;
                }
            }
```

- Caso o caracter seja uma letra, armazena ele na palavra auxiliar e incrementa o tamanho da palavra.
```c
else
    auxPalavra[sizePalavra++] = c;
```
### 2.4) Vetor de frequências
Cria dinamicamente um vetor de (celula *), com tamanho da frequência máxima + 1, 
em que cada índice i do vetor corresponde a lista ligada de palavras com
frequência i.

A inserção das palavras nas listas ligadas do vetor é feito por meio da função inordem,
 que percorre a árvore binária em ordem alfabética e insere a palavra de freqência i na lista
 ligada com inicio em  frequencias[ i ].
```c
    celula ** frequencias = malloc(sizeof(celula *) * (maxFreq + 1));

    inordem(raiz, frequencias);
```

### 2.5) Input dos Ks
- Enquanto k for diferente de zero, recebe novos ks.
- O k deve ser menor ou igual a frequência máxima , ou não haverá uma lista ligada correspondente.
- Imprime em ordem alfabética as palavras com frequência k.
```c
    while(k != 0){
    printf("Digite um k (menor  ou igual a %d): ", maxFreq );
    scanf("%d", &k);

    if(k > maxFreq)
        printf("Nao ha frequencias maiores que %d\n", maxFreq);

    
    else
        imprimeListaRec(frequencias[k]);

    }
```

### 2.6) Liberação de memória
Libera as memórias alocadas dinamicamente.
```c
   free(palavra);
    for(i = 0; i < maxFreq + 1; i++){
        free(frequencias[i]);
    }
```
## 3) Testes

Para testar, basta modificar o conteúdo
do arquivo "example.txt" e testar com os Ks 
que desejar durante a execução do código.

- Para o texto (música "Epitáfio" do titãs):
```txt
Devia ter amado mais
Ter chorado mais
Ter visto o sol nascer
Devia ter arriscado mais
E ate errado mais
Ter feito o que eu queria fazer
Queria ter aceitado
As pessoas como elas sao
Cada um sabe a alegria
E a dor que traz no coracao
O acaso vai me proteger
Enquanto eu andar distraido
O acaso vai me proteger
Enquanto eu andar
Devia ter complicado menos
Trabalhado menos
Ter visto o sol se por
Devia ter me importado menos
Com problemas pequenos
Ter morrido de amor
Queria ter aceitado
A vida como ela e
A cada um cabe alegrias
E a tristeza que vier
O acaso vai me proteger
Enquanto eu andar distraido
O acaso vai me proteger
Enquanto eu andar
O acaso vai me proteger
Enquanto eu andar distraido
O acaso vai me proteger
Enquanto eu andar
Devia ter complicado menos
Trabalhado menos
Ter visto o sol se por
```

Saída para os seguintes Ks :

- k = 2
```txt
aceitado
cada
como
complicado
por
se
trabalhado
um

```
- k = 3
```txt
distraido
que
queria
sol
visto
```
- k = 13
```txt
ter

```