#include <stdlib.h>
#include <stdio.h>

/*
#################### LINKEDLIST
Pede um endere�o p/ mem�ria, mas como n�o � algo cont�nuo, � necess�rio uma informa��o a mais
Essa informa��o � o endere�o do pr�ximo bloco/n� onde o valor ser� armazenado
O 0 serve para marcar o fim da lista, j� que � um endere�o inv�lido
*/

struct no {
    int val; // 4 bytes
    struct no* prox; // 4 bytes

    // Possui 8 bytes, e � chamado de n�
    // O primeiro n� � chamado de cabe�a, cujo endere�o 
    // � mantido o tempo todo
    // O �ltimo n� � null ou 0
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
    // enquanto o pr�ximo n� for diferente de null, o n� atual vai ficar recebendo o pr�ximo

    if (lista->cabeca == NULL) { // caso HEAD seja igual NULL, isto �, n�o tenha endere�o
        struct no* noNovo = alocarNovoNo(valor); // chamando a fun��o
        lista->cabeca = noNovo; // o pr�ximo n� recebe o n� novo
    }
    else { // se HEAD for NULL
        struct no* temp = lista->cabeca; // criando temp recebendo um valor diferente de NULL
        while (temp->prox != NULL) {  // enquanto o pr�ximo endere�o for diferente de NULL...
            temp = temp->prox;  // ...o atual recebe o pr�ximo endere�o

        }
        struct no* noNovo = alocarNovoNo(valor); // chamando a fun��o
        temp->prox = noNovo;

    }
    lista->qtdade++;
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor) {

    // head[100]->[x|120]->[y|210]->[z| ]->NULL
    // adicionando ao in�cio
    // mudar a head para o endere�o que deve ser apontado
    // mudar o que foi adicionado para apontar para o pr�ximo n�
    // aumentar qtdade

    if (lista->cabeca == NULL) { // caso n�o haja nenhum n�
        struct no* noNovo = alocarNovoNo(valor);
        lista->cabeca = noNovo; // recebe o novo
    }
    else {
        struct no* noNovo = alocarNovoNo(valor);
        noNovo->prox = lista->cabeca; // o pr�ximo endere�o vai ser o que era o da head
        lista->cabeca = noNovo;
    }

    lista->qtdade++;
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao) {
    // a posicao � identificada
    // a primeira e a �ltima tem que criar uma cond e usar as fun��es criadas para in�cio e fim
    // percorrer a lista, iniciando da head, at� encontrar a posi��o
    // um novo n� � inserido ap�s a posicao fornecida

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
        //navega partindo da cabe�a at� chegar NULL
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
        printf("A lista est� vazia!");
    }
}