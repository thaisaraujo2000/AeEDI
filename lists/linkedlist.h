#include <stdlib.h>
#include <stdio.h>

/*
#################### LINKEDLIST
Pede um endereço p/ memória, mas como não é algo contínuo, é necessário uma informação a mais
Essa informação é o endereço do próximo bloco/nó onde o valor será armazenado
O 0 serve para marcar o fim da lista, já que é um endereço inválido
*/

struct no {
    int val; // 4 bytes
    struct no* prox; // 4 bytes

    // Possui 8 bytes, e é chamado de nó
    // O primeiro nó é chamado de cabeça, cujo endereço 
    // é mantido o tempo todo
    // O último nó é null ou 0
};


struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar() {
    struct linkedlist* lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));
    lista->cabeca = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* noNovo = (struct no*)malloc(sizeof(struct no));
    noNovo->val = valor;
    noNovo->prox = NULL;
    return noNovo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {
    // elemento no fim:
    // [head = 204] -> [x|204] -> [x|NULL] 
    // enquanto o próximo nó for diferente de null, o nó atual vai ficar recebendo o próximo

    if (lista->cabeca == NULL) { // caso HEAD seja igual NULL, isto é, não tenha endereço
        struct no* noNovo = alocarNovoNo(valor); // chamando a função
        lista->cabeca = noNovo; // o próximo nó recebe o nó novo
    }
    else { // se HEAD for NULL
        struct no* temp = lista->cabeca; // criando temp recebendo um valor diferente de NULL
        while (temp->prox != NULL) {  // enquanto o próximo endereço for diferente de NULL...
            temp = temp->prox;  // ...o atual recebe o próximo endereço

        }
        struct no* noNovo = alocarNovoNo(valor); // chamando a função
        temp->prox = noNovo;

    }
    lista->qtdade++;
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor) {

    // head[100]->[x|120]->[y|210]->[z| ]->NULL
    // adicionando ao início
    // mudar a head para o endereço que deve ser apontado
    // mudar o que foi adicionado para apontar para o próximo nó
    // aumentar qtdade

    if (lista->cabeca == NULL) { // caso não haja nenhum nó
        struct no* noNovo = alocarNovoNo(valor);
        lista->cabeca = noNovo; // recebe o novo
    }
    else {
        struct no* noNovo = alocarNovoNo(valor);
        noNovo->prox = lista->cabeca; // o próximo endereço vai ser o que era o da head
        lista->cabeca = noNovo;
    }

    lista->qtdade++;
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao) {
    // a posicao é identificada
    // a primeira e a última tem que criar uma cond e usar as funções criadas para início e fim
    // percorrer a lista, iniciando da head, até encontrar a posição
    // um novo nó é inserido após a posicao fornecida

    if (posicao >= 0 && posicao <= lista->qtdade) {
        if (posicao == 0) {
            inserirElementoNoInicio(lista, valor);
        }
        else if (posicao == lista->qtdade) {
            inserirElementoNoFim(lista, valor);
        }
        else {
            struct no* temp = lista->cabeca;
            int i = 0;
            while (i < posicao - 1) {
                temp = temp->prox;
                i++;
            }
            struct no* noNovo = alocarNovoNo(valor);
            noNovo->prox = temp->prox;
            temp->prox = noNovo;
            lista->qtdade++;
        }
    }
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    struct no* temp = lista->cabeca;
    if (posicao >= 0 && posicao <= lista->qtdade) {

        int i = 0;

        while (temp != NULL) {
            if (i == posicao) {
                return temp->val;
            }

            temp = temp->prox;
            i++;
        }
    }
}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) {
        if (posicao == 0) {
            struct no* temp_aux = lista->cabeca;
            lista->cabeca = temp_aux->prox;
            free(temp_aux);
            lista->qtdade--;
        }
        else {
            struct no* temp = lista->cabeca;

            int i = 0;
            while (i < posicao - 1) {
                temp = temp->prox;
                i++;
            }

            struct no* temp_aux = temp->prox;
            temp->prox = temp_aux->prox;
            free(temp_aux);
            lista->qtdade--;
        }
    }
}

void imprimirLista(struct linkedlist* lista) {
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista está vazia!");
    }
}