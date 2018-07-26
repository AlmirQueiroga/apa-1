//
//  main.c
//  selectionsort
//
//  Created by Karina Villarim on 7/26/18.
//  Copyright © 2018 Karina Villarim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 10

void SelectionSort(int *array){
    int i, j, menor, aux;
    
    for(i = 0; i <= MAX_ELEMENTOS - 1; i++){
        menor = i;
        for(j = i+1; j <= MAX_ELEMENTOS - 1; j++){
            if(*(array + j) < *(array + menor)){
                menor = j;
            }
        }
        if(*(array + i) != *(array + menor)){
            aux = *(array + i);
            *(array + i) = *(array + menor);
            *(array + menor) = aux;
        }
    }
}

int main(){
    //nesse codigo nao existe melhor e pior caso
    int array[MAX_ELEMENTOS] = {4,6,2,9,5,1,7,8,3,0};//array aleatorio
    int i = 0;
    
    SelectionSort(array);
    
    printf("{");
    for(i = 0; i <= MAX_ELEMENTOS - 1; i++){
        printf("%d,", array[i]);
    }
    printf("}");
    
    return 0;
}


