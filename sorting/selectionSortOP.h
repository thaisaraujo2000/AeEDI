#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int* selectionSortOP(int* v, int tam) {
  int* v_ordenado = (int*)calloc(tam, sizeof(int));

  for(int i = 0; i<tam; i++){
    int i_menor = i;
    for(int j = 0; j<tam; j++){
      if(v[i_menor]>v[j]){
        i_menor = j;
      }
    }
    v_ordenado[i] = v[i_menor];
    v[i_menor] = INT_MAX;
  }
  return v_ordenado;
}