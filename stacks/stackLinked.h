#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedstack {
    struct no* topo;
    int qtdade;
};

struct linkedstack* inicializar() {
    struct linkedstack* pilha = (struct linkedstack*)malloc(sizeof(struct linkedstack));
    pilha->topo = NULL;
    pilha->qtdade = 0;
    return pilha;
}

struct no* alocarNovoNo(int valor) {
    struct no* noNovo = (struct no*)malloc(sizeof(struct no));
    noNovo->val = valor;
    noNovo->prox = NULL;
    return noNovo;
}

//retornar true se a pilha for nula ou vazia
bool vazia(struct linkedstack* pilha) {
    if (pilha == NULL || pilha->qtdade == 0) {
        return true;
    }
    else {
        return false;
    }
}

//se a pilha estiver nula, instancie a pilha
//por causa da possibilidade de instanciacao usamos struct linkedstack**
void empilhar(struct linkedstack** pilha, int valor) {
    if ((*pilha) == NULL) {
        (*pilha) = inicializar();
        struct no* noNovo = alocarNovoNo(valor);
        (*pilha)->topo = noNovo;
        (*pilha)->qtdade++;
    }
    else {
        struct no* noNovo = alocarNovoNo(valor);
        struct no* temp = (*pilha)->topo; // temp recebe o topo atual
        (*pilha)->topo = noNovo; //o topo vai receber o novo nó
        noNovo->prox = temp; // o novo nó vai apontar para o próximo nó, que era o valor do topo
        (*pilha)->qtdade++; // incremento
    }
}

//decrementar qtdade se a pilha não estiver nula ou vazia
void desempilhar(struct linkedstack* pilha) {
    if (pilha == NULL || pilha->qtdade == 0) {
        return;
    }
    else {
        struct no* temp = pilha->topo; // temp recebe o topo atual
        pilha->topo = temp->prox;// como eu quero remover ele, ele tem que apontar para o próximo nó
        pilha->qtdade--; // decremento
        free(temp);
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct linkedstack* pilha) {
    if (pilha == NULL || pilha->qtdade == 0) {
        return INT_MIN;
    }
    else {
        struct no* temp = pilha->topo; // temp recebe o topo atual
        int valorDesempilhado = temp->val; // recebe o valor atual
        pilha->topo = temp->prox;// como eu quero remover ele, ele tem que apontar para o próximo nó
        pilha->qtdade--; // decremento
        free(temp);
        return valorDesempilhado;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct linkedstack* pilha) {
    if (pilha == NULL || pilha->qtdade == 0) {
        return INT_MIN;
    }
    else {
        struct no* temp = pilha->topo;
        return temp->val;
    }
}

void exibirPilha(struct linkedstack* pilha) {
    //usamos o aux para percorrer a lista
    if (!vazia(pilha)) {
        struct no* aux = pilha->topo;
        //navega partindo do topo até chegar NULL
        printf("_\n");
        do {
            printf("%d\n", aux->val);
            aux = aux->prox;
        } while (aux != NULL);
        printf("_");
    }
    else {
        printf("A pilha está vazia!");
    }
}
