#include <stdio.h>
#include <stdlib.h>

struct arraylist {
    int* vetor;
    int qtdade;
    int capacidade;
};

struct arraylist* inicializar(int capacidade) {
    struct arraylist* lista = (struct arraylist*)malloc(sizeof(struct arraylist));
    lista->vetor = (int*)calloc(capacidade, sizeof(int));
    lista->qtdade = 0; // evitar inicializar com lixo
    lista->capacidade = capacidade;
    return lista;
}

int obterElementoEmPosicao(struct arraylist* lista, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) {
        return lista->vetor[posicao];
    }
}

void duplicarCapacidade(struct arraylist* lista) {
    lista->vetor = (int*)realloc(lista->vetor, 2 * lista->capacidade * sizeof(int)); //realocando(ponteiro para um bloco de memoria que seu código, novo tamanho)
    lista->capacidade = 2 * lista->capacidade; //capacidade duplicada
}

void inserirElementoNoFim(struct arraylist* lista, int valor) {
    //verificar se a qtd é igual à capacidade
    //caso seja, duplicar lista
    //adicionando o valor à última posição, que corresponde à qtd
    //como a qtd aumentou, qtd++
    if (lista->qtdade == lista->capacidade) {
        duplicarCapacidade(lista);
    }
    lista->vetor[lista->qtdade] = valor;
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct arraylist* lista, int valor, int posicao) {
    int i = lista->qtdade;
    if (posicao >= 0 && posicao <= lista->qtdade) {
        if (lista->qtdade == lista->capacidade) {
            duplicarCapacidade(lista);
        }
        while (posicao < i) {
            lista->vetor[i] = lista->vetor[i - 1];
            i--;
        }
        lista->vetor[posicao] = valor;
        lista->qtdade++;
    }
}

void atualizarElemento(struct arraylist* lista, int valor, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) {
        lista->vetor[posicao] = valor;
    }
}

void removerElementoNoFim(struct arraylist* lista) {
    lista->qtdade--;
}

void removerElementoEmPosicao(struct arraylist* lista, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) {
        while (posicao < lista->qtdade - 1) {
            lista->vetor[posicao] = lista->vetor[posicao + 1];
            posicao++;
        }
        lista->qtdade--;
    }
    //0 1 2 3
    //3 5 9 7
    //quero remover posicao 0 (valor 3)
    //3 3 
}

void exibirLista(struct arraylist* lista) {
    printf("[");
    for (int i = 0; i < lista->qtdade; i++) {
        printf("%d", lista->vetor[i]);
        if (i < lista->qtdade - 1) {
            printf(", ");
        }
    }
    printf("]");
}