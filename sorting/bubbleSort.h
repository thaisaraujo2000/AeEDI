#include <stdio.h>
#include <stdbool.h>

void bubbleSort(int* v, int tam) {
  for(int i = 0; i<tam-1; i++){
    bool trocou = false;
    for(int j = 0; j<tam-1; j++) {
      if(v[j]>v[j+1]){
        int aux = v[j];
        v[j] = v[j+1];
        v[j+1] = aux;
        trocou = true;
      }
    }
    if(trocou==false) {
      return;
    }
  }
}