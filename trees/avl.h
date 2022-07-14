#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

//void atualizar(struct noBstAvl* no);

struct noBstAvl* balancear(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no);


struct avl {
    struct noBstAvl* raiz;
    int tam;
};

struct noBstAvl {
    int val;
    int altura;
    int balanco;
    struct noBstAvl* esq;
    struct noBstAvl* dir;
};

/**
 * Funcao que aloca uma nova arvore avl.
 **/
struct avl* alocarAvl() {
    struct avl* arvore = (struct avl*)malloc(sizeof(struct avl));
    arvore->raiz = NULL;
    arvore->tam = 0;
    return arvore;
}

/**
 * Funcao que aloca um novo noBstAvl, e
 * ajusta os ponteiros esq e dir para NULL,
 * e variáveis altura e balanco para 0.
 **/
struct noBstAvl* alocarNovoNo(int val) {
    struct noBstAvl* novoNo = (struct noBstAvl*)malloc(sizeof(struct noBstAvl));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 0;
    novoNo->balanco = 0;
    novoNo->val = val;

    return novoNo;
}


/**
 * Funcao que retorna o maior valor de uma árvore AVL.
 * Mesma implementação da BST.
 **/
int max(struct noBstAvl* raiz) {
    if (raiz == NULL) {
        return -1;
    }
    if (raiz->dir != NULL) {
        return max(raiz->dir);
    }
    else {
        return raiz->val;
    }
}

/**
 * Funcao que retorna o menor valor de uma árvore AVL.
 * Mesma implementação da BST.
 **/
int min(struct noBstAvl* raiz) {
    if (raiz == NULL) {
        return -1;
    }
    if (raiz->esq != NULL) {
        return min(raiz->esq);
    }
    else {
        return raiz->val;
    }
}

/**
 * Funcao que recebe a raiz de uma bstAvl e atualiza sua altura
 * e fator de balanço.
 * Lembre que a altura das sub-árvores direita e esquerda
 * não vão mudar, por isso a implementação não é tão complicada.
 **/

void atualizar(struct noBstAvl* no) {
    int alturaDir = -1;
    int alturaEsq = -1;

    if (no == NULL) {
        return;
    }
    else {
        if (no->dir != NULL) {
            alturaDir = no->dir->altura;
        }
        if (no->esq != NULL) {
            alturaEsq = no->esq->altura;
        }

        if (alturaEsq >= alturaDir) {
            no->altura = 1 + alturaEsq;
        }
        else {
            no->altura = 1 + alturaDir;
        }

        no->balanco = alturaDir - alturaEsq;
    }
}


/**
 * Funcao que rotaciona uma arvore para a
 * direita e retorna a nova raiz.
 **/
struct noBstAvl* rotacaoDireita(struct noBstAvl* arvore) {
    struct noBstAvl* esqRaiz = arvore->esq;

    arvore->esq = esqRaiz->dir;
    esqRaiz->dir = arvore;

    atualizar(arvore);
    atualizar(esqRaiz);

    return esqRaiz;
}

/**
 * Funcao que rotaciona uma arvore para a
 * esquerda e retorna a nova raiz.
 **/
struct noBstAvl* rotacaoEsquerda(struct noBstAvl* arvore) {
    struct noBstAvl* dirRaiz = arvore->dir;

    arvore->dir = dirRaiz->esq;
    dirRaiz->esq = arvore;
    atualizar(arvore);
    atualizar(dirRaiz);

    return dirRaiz;

}


/**
 * Funcao que recebe a raiz de uma bstAvl, e
 * insere um novo valor nela.
 * Raiz é passada por referência (ponteiro de ponteiro).
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó inserido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de inserir de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/
void inserirNo(struct noBstAvl* raiz, struct noBstAvl* novoNo) {
    if (raiz->val > novoNo->val) { // caso 1: valor da raiz maior do que o do novoNo: inserir na esquerda
        if (raiz->esq == NULL) { // raiz esq NULL
            raiz->esq = novoNo;
        }
        else { // raiz esq não NULL
            inserirNo(raiz->esq, novoNo);
        }
    }
    else if (raiz->val <= novoNo->val) { // caso 2: valor da raiz menor do que o do novoNo: inserir na direita
        if (raiz->dir == NULL) {
            raiz->dir = novoNo;
        }
        else {
            inserirNo(raiz->dir, novoNo);
        }
    }
    atualizar(raiz);
    (raiz) = balancear(raiz);
}

/**
 * Funcao fachada para insercao, similar a funcao de
 * insercao na BST.
 * Lembrar de incrementar tamanho.
 **/
void inserir(struct avl* avl, int val) {
    struct noBstAvl* noNovo = alocarNovoNo(val);

    if (avl->raiz == NULL) {
        avl->raiz = noNovo;
    }
    else {
        inserirNo(avl->raiz, noNovo);
    }
    avl->tam++;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e identifica em qual caso
 * ela se encaixa para executar os procedimentos de balanceamento
 * corretos:
 *      - Caso 1: esquerda-esquerda e esquerda-cheio
 *      - Caso 2: esquerda-direita
 *      - Caso 3: direita-direita e direita-cheio
 *      - Caso 4: direita-esquerda
 * Lembrar que quando há balanceamento temos uma nova raiz
 * que deve ser retornada para a função que chama o balanceamento.
 * Dica: usar fator de balanço do nó e de uma de suas sub-árvores
 * para descobrir qual é o caso.
 **/
struct noBstAvl* balancear(struct noBstAvl* no) {
    if (no->balanco == -2) {
        if (no->esq->balanco <= 0) {
            no = rebalancearEsqEsq(no);
        }
        else {
            no = rebalancearEsqDir(no);
        }
    }

    if (no->balanco == 2) {
        if (no->dir->balanco <= 0) {
            no = rebalancearDirEsq(no);
        }
        else {
            no = rebalancearDirDir(no);
        }
    }

    return no;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 1.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no) {
    return rotacaoDireita(no);
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 2.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no) {
    no->esq = rotacaoEsquerda(no->esq);

    return rebalancearEsqEsq(no);
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 3.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no) {
    return rotacaoEsquerda(no);
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 4.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no) {
    no->dir = rotacaoDireita(no->dir);

    return rebalancearDirDir(no);
}

/**
 * Funcao que recebe a raiz de uma árvore AVL, e
 * remove o nó que contem o valor passado como
 * argumento.
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó removido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de remover de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/
struct noBstAvl* removerNo(struct noBstAvl* raiz, int val) {
    if (raiz == NULL) {
        return raiz;
    }
    else if (raiz != NULL) {
        if (val < raiz->val) {
            raiz->esq = removerNo(raiz->esq, val);
        }
        else if (val < raiz->val) {
            raiz->dir = removerNo(raiz->dir, val);
        }
        else {
            // achei o nó que precisa ser removido
            if (raiz->esq == NULL && raiz->dir == NULL) {
                // caso 1 - no folha
                free(raiz);
                return NULL;
            }
            // caso 2
            if (raiz->esq != NULL && raiz->dir == NULL) {
                struct noBstAvl* aux = raiz->esq;
                free(raiz);
                return aux;
            }
            else if (raiz->esq == NULL && raiz->dir != NULL) {
                struct noBstAvl* aux = raiz->dir;
                free(raiz);
                return aux;
                //caso 3
            }
            else {
                int minimo = min(raiz->dir);
                raiz->val = minimo;
                removerNo(raiz->dir, raiz->val);
            }
        }
        atualizar(raiz);
        balancear(raiz);
    }
}

/**
 * Funcao fachada para remocao, similar a funcao de
 * remocao na BST.
 * Lembrar de decrementar tamanho.
 **/
void remover(struct avl* avl, int val) {
    if (avl->raiz != NULL) {
        struct noBstAvl* no = removerNo(avl->raiz, val);
        if (no != NULL) {
            avl->raiz = no;
        }
        avl->tam--;
    }
}

void imprimir(queue<struct noBstAvl*> nosImpressao);

/**
* Função que imprime a árvore.
* Pode ser útil para depuração.
**/
void imprimir(struct noBstAvl* raiz) {
    queue<struct noBstAvl*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBstAvl*> nosImpressao) {

    queue<struct noBstAvl*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBstAvl* noImpressao = nosImpressao.front();
        //add filhos na fila
        if (noImpressao != NULL) {
            if (noImpressao->esq != NULL)
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL)
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL) {
            cout << to_string(noImpressao->val) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if (!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
}