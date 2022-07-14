#include <stdio.h>
#include <stdlib.h>

void countingSort(int* v, int tam){
  // descobrir maior e menor valor do vetor
  int menor, maior = v[0];

  for(int i = 0; i<tam; i++){
    if(v[i]<menor){
      menor = v[i];
    }
    if(v[i]>maior){
      maior = v[i];
    }
  }

  // construir vetor de ocorrência/contagem
  int tamVOcorrencias = maior-menor+1; 
  int* vOcorrencias = (int*)calloc(tamVOcorrencias, sizeof(int)); 

  for(int i = 0; i<tam; i++){
    int valor = v[i];
    vOcorrencias[valor-menor]++;
  }

  // somar cumulativamente o array de contagem
  for(int i = 1; i<tamVOcorrencias; i++){
    vOcorrencias[i] += vOcorrencias[i-1];
  }

  int* vOrdenado = (int*)calloc(tamVOcorrencias,sizeof(int));

  //obter vetor ordenado
  for(int i = 0; i<tam; i++){
    int valor = v[i];
    int indexVOcorrencias = vOcorrencias[valor - menor];
    int indexVetorOrdenado = indexVOcorrencias-1;
    vOrdenado[indexVetorOrdenado] = valor;
    vOcorrencias[valor - menor]--; 
  }
}