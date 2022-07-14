#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct noBst {
    struct noBst* esq;
    struct noBst* dir;
    int valor;
};

struct bst {
    struct noBst* raiz;
    int tam;
};

struct bst* alocarBst() {
    struct bst* bst = (struct bst*)malloc(sizeof(struct bst));
    bst->raiz = NULL;
    bst->tam = 0;
    return bst;
}

struct noBst* alocarNovoNo(int val) {
    struct noBst* noNovo = (struct noBst*)malloc(sizeof(struct noBst));
    noNovo->esq = NULL;
    noNovo->dir = NULL;
    noNovo->valor = val;
    return noNovo;
}

void inserirNoIt(struct noBst* raiz, struct noBst* novoNo) {
    while (raiz != NULL) {
        if (raiz->valor >= novoNo->valor) { // caso 1: inserir na esquerda
            if (raiz->esq == NULL) {
                raiz->esq = novoNo;
                return;
            }
            else {
                raiz = raiz->esq; // novo nó
            }
        }
        else { // caso 2: inserir na direita
            if (raiz->dir == NULL) {
                raiz->dir = novoNo; // novo nó
                return;
            }
            else {
                raiz = raiz->dir;
            }
        }
    }
}

void inserirNoRec(struct noBst* raiz, struct noBst* novoNo) {
    if (raiz->valor >= novoNo->valor) { // caso 1: valor da raiz maior do que o do novoNo: inserir na esquerda
        if (raiz->esq == NULL) { // raiz esq NULL
            raiz->esq = novoNo;
        }
        else { // raiz esq não NULL
            inserirNoRec(raiz->esq, novoNo);
        }
    }
    else if (raiz->valor < novoNo->valor) { // caso 2: valor da raiz menor do que o do novoNo: inserir na direita
        if (raiz->dir == NULL) {
            raiz->dir = novoNo;
        }
        else {
            inserirNoRec(raiz->dir, novoNo);
        }
    }
}

void inserir(struct bst* bst, int val, bool rec) {
    struct noBst* noNovo = alocarNovoNo(val);

    if (bst->raiz == NULL) {
        bst->raiz = noNovo;
    }
    else if (rec) {
        inserirNoRec(bst->raiz, noNovo);
    }
    else {
        inserirNoIt(bst->raiz, noNovo);
    }
    bst->tam++;
}

bool buscarRec(struct noBst* raiz, int val) {
    if (raiz == NULL) {
        return false;
    }
    else if (raiz->valor == val) {
        return true;
    }
    else if (raiz->valor >= val) {
        return buscarRec(raiz->esq, val);
    }
    else if (raiz->valor <= val) {
        return buscarRec(raiz->dir, val);
    }
}

bool buscarIt(struct noBst* raiz, int v) {
    while (raiz != NULL) {
        if (raiz->valor > v) {
            raiz = raiz->esq;
        }
        else if (raiz->valor < v) {
            raiz = raiz->dir;
        }
        else {
            return true;
        }
    }
    return false;
}

bool buscar(struct bst* bst, int val, bool rec) {
    if (bst->raiz == NULL) {
        return false;
    }
    else if (rec) {
        return buscarRec(bst->raiz, val);
    }
    else {
        return buscarIt(bst->raiz, val);
    }
    bst->tam++;
}

void navEmOrdem(struct noBst* raiz) {
    if (raiz != NULL) {
        navEmOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        navEmOrdem(raiz->dir);
    }
}

void navPreOrdem(struct noBst* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        navEmOrdem(raiz->esq);
        navEmOrdem(raiz->dir);
    }
}

void navPosOrdem(struct noBst* raiz) {
    if (raiz != NULL) {
        navEmOrdem(raiz->esq);
        navEmOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

int min(struct noBst* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->esq != NULL) {
        return min(raiz->esq);
    }
    else {
        return raiz->valor;
    }
}

int max(struct noBst* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->dir != NULL) {
        return max(raiz->dir);
    }
    else {
        return raiz->valor;
    }
}

int altura(struct noBst* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    else {
        int hdir = 0;
        int hesq = 0;
        if (raiz->esq != NULL) {
            hesq = 1 + altura(raiz->esq);
        }
        if (raiz->dir != NULL) {
            hdir = 1 + altura(raiz->dir);
        }
        if (hdir >= hesq) {
            return hdir;
        }
        else {
            return hesq;
        }
    }
}

struct noBst* removerRec(struct noBst* raiz, int val) {
    if (raiz != NULL) {
        if (val < raiz->valor) {
            raiz->esq = removerRec(raiz->esq, val);
        }
        else if (val > raiz->valor) {
            raiz->dir = removerRec(raiz->dir, val);
        }
        else {
            if (raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                raiz = NULL;
                return raiz;
            }
            if (raiz->esq != NULL && raiz->dir == NULL) {
                struct noBst* aux = raiz;
                raiz = raiz->esq;
                free(aux);
                return raiz;
            }
            else if (raiz->esq == NULL && raiz->dir != NULL) {
                struct noBst* aux = raiz;
                raiz = raiz->dir;
                free(aux);
                return raiz;
            }
            else {
                int minimo = min(raiz->dir);
                raiz->valor = minimo;
                removerRec(raiz->dir, raiz->valor);
            }
        }
    }
    return raiz;
}

// caso 1: nó folha
// - navegar até o pai
// - desalocar nó folha
// - pai -> filho (esq/dir) == NULL

// caso 2: nó só tem um filho
// - navegar até o pai
// - aux apontando p/ o filho do nó a ser removido
// - deslocar o nó a ser removido
// - atualizar o filho do nó pai para aux

// caso 3: nó tem 2 filhos
// aux = min(raiz->dir)
// aux->esq = raiz->esq
// aux->dir = raiz->dir
// 1: trazer para a pos do nó removido min(noRemovido->dir)
// 2: trazer para a pos do nó removido max(noRemovido->esq)

void remover(struct bst* bst, int val) {
    if (bst->raiz == NULL) {
        return;
    }
    else {
        removerRec(bst->raiz, val);
    }
    bst->tam--;
}