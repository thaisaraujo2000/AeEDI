#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedqueue {
    struct no* frente;
    struct no* tras;
    int qtdade;
};

struct linkedqueue* inicializar() {
    struct linkedqueue* fila = (struct linkedqueue*)malloc(sizeof(struct linkedqueue));
    fila->frente = NULL;
    fila->qtdade = 0;
    fila->tras = NULL;
    return fila;
}

struct no* alocarNovoNo(int valor) {
    struct no* noNovo = (struct no*)malloc(sizeof(struct no));
    noNovo->val = valor;
    noNovo->prox = NULL;
    return noNovo;
}

bool vazia(struct linkedqueue* fila) {
    if (fila == NULL || fila->qtdade == 0) {
        return true;
    }
    else {
        return false;
    }
}

//se a fila estiver nula, instancie a fila
//por causa da possibilidade de instanciacao usamos struct linkedqueue**
void enfileirar(struct linkedqueue** fila, int val) {
    if ((*fila) == NULL) {
        (*fila) = inicializar();
    }
    if ((*fila)->qtdade == 0){
      struct no* noNovo = alocarNovoNo(val);
      (*fila)->frente = noNovo;
      (*fila)->tras = noNovo;
       (*fila)->qtdade++;
    }
    else {
        struct no* noNovo = alocarNovoNo(val);
        struct no* temp = (*fila)->tras;
        
        temp->prox = noNovo;
        (*fila)->tras = noNovo;
        (*fila)->qtdade++;

    }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
//lembrem de desalocar o nó removido (free)
int desenfileirar(struct linkedqueue* fila) {
    if (vazia(fila)==true) {
        return INT_MIN;
    }
    else if (fila->qtdade == 1) {
            struct no* temp = fila->frente;
            int valorRemovido = temp->val;
            fila->frente = fila->tras = NULL;
            fila->qtdade--;
            free(temp);
            return valorRemovido;
     }
     else {
            struct no* temp = fila->frente;
            int valorRemovido = temp->val;

            fila->frente = temp->prox;
            fila->qtdade--;
            free(temp);
            return valorRemovido;
        
    } 

}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct linkedqueue* fila){
    if (fila == NULL || fila->qtdade == 0) {
        return INT_MIN;
    }
    else {
        struct no* temp = fila->frente;
        int valorFrente = temp->val;
        return temp->val;
    }
}
