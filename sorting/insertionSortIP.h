#include <stdio.h>

int* insertionSortIP(int* v, int tam) {
  for(int i = 1; i<tam; i++){
    
    int j = i-1;
    while(j >= 0 && v[j+1]<v[j]){
      int aux = v[j];
      v[j] = v[j+1];
      v[j+1] = aux;
      j--;
    }
    //8 | 9 | 7
    
    //0   1   2
    //i = 1
    //j = 0
    //j > 0 e 8>9? X

    //i = 2
    //j = 1
    //j >= 1 e 7 < 9? V
    //aux = 7
    //v[2] = 9
    //v[1] = 7

    //8 | 7 | 9
    
    //i = 1
    //j = 0
    //j >= 0 e 7 < 8? V
    //aux = 8
    //v[1] = 9
    //v[0] = 8

    }
  return v;
}