#include <stdio.h>
#include <stdlib.h>

void selectionSortIP(int* v, int tam){
  int aux = 0;
  int i_menor = 0;
  for(int i = 0; i<tam-1; i++) {
    i_menor = i;
    for(int j= i+1; j<tam; j++){
      if(v[i_menor]>v[j]){
        i_menor = j;
      }
    }
    aux = v[i];
    v[i] = v[i_menor];
    v[i_menor] = aux;
  }
}