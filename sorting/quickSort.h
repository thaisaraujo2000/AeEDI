#include <stdio.h>
#include <stdlib.h>

void swap(int* v, int i, int j) {
  int aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

int particiona(int* v, int inicio, int fim){
  int pIndex = inicio;
  
  srand(time(NULL));
  int random = inicio + rand() % (fim - inicio);
  swap(v, random, fim);

  int pivo = v[fim];

  
  for(int i = inicio; i<fim; i++){
    if(v[i] <= pivo){
      swap(v, i, pIndex);
      pIndex++;
    }
  }
  swap(v, pIndex, fim);
  return pIndex;
}

void quickSort(int* v, int inicio, int fim){
  if (inicio < fim) {

      int pIndex = particiona(v, inicio, fim);

      quickSort(v, inicio, pIndex-1);
      quickSort(v, pIndex+1, fim);

  }
}