#include <stdio.h>
#include <stdlib.h>

// meio/2
// sub vetores
//compara eles e vai juntando

void merge(int* v, int tam, int* vL, int tam_vL, int* vR, int tam_vR) {

    // vetores
    int i_v = 0;
    int i_vL = 0;
    int i_vR = 0;

    // vetores L e R até seus respectivos tamanhos
    while (i_vL < tam_vL && i_vR < tam_vR) {
        int menor;

        // se o valor do vetor da esquerda for menor do que o da direita, o vL será guardado
        if (vL[i_vL] <= vR[i_vR]) {
            menor = vL[i_vL];
            i_vL++;
        }
        // senão, o menor é vR
        else {
            menor = vR[i_vR];
            i_vR++; // subo uma posição
        }

        v[i_v] = menor; // adiciono o menor em v
        i_v++;
    }
    // enquanto o índice da esquerda for menor do que o da direita
    // v vai receber o vetor da esquerda
    // subo uma posição no esquerdo e no vetor ordenado
    while (i_vL < i_vR) {
        v[i_v] = vL[i_vL];
        i_v++;
        i_vL++;
    }

    // mesma coisa, mas agora para o lado direito
    while (i_vR < tam_vR) {
        v[i_v] = vR[i_vR];
        i_v++;
        i_vR++;
    }

}

void mergeSort(int* v, int tam) {
    if (tam > 1) {
        int tam_v = tam; // tamanho do vetor

        int meio = tam / 2; // meio

        // tamanho dos vetores gerados com a divisão
        int tam_vL = meio;
        int tam_vR = tam - meio;

        int* vL = (int*)calloc(tam_vL + 1, sizeof(int));
        // vetor left recebendo seus elementos (até meio)
        for (int i = 0; i < meio; i++) {
            vL[i] = v[i];
            // printf("%d", vL[i]);
        }
        // printf(" VL \n");

        int* vR = (int*)calloc(tam_vR, sizeof(int));

        // realizando a recursão para realizar a divisão
        mergeSort(vL, tam_vL);
        mergeSort(vR, tam_vR);
        // unindo e ordenando
        merge(v, tam_v, vL, tam_vL, vR, tam_vR);
    }

}