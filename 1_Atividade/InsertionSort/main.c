//
//  main.c
//  insertionsort
//
//  Created by Karina Villarim on 7/26/18.
//  Copyright © 2018 Karina Villarim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 10

void InsertionSort(int *array){
    int i, j;
    int pivo;
    
    for(i = 1; i <= MAX_ELEMENTOS - 1; i++){
        
        pivo = *(array + i);
        j = i - 1;
        
        while(j >= 0 && *(array + j) > pivo){
            
            *(array + (j+1)) = *(array + j);
            j = j - 1;
            
        }
        *(array + (j+1)) = pivo;
    }
}

int main(void){
    
    int array[MAX_ELEMENTOS] = {4,2,9,5,1,7,8,3,0,6};
    int i = 0;
    
    InsertionSort(array);
    
    printf("{");
    for(i = 0; i <= MAX_ELEMENTOS - 1; i++){
        printf("%d,", array[i]);
    }
    printf("}");
    
    return 0;
}
