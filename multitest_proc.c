// this file is for multiprocessing
#include <stdlib.h>
#include <stdio.h>
int search(int target, int* list, int size) {
    int i;
    for(i = 0; i < 2; i++) {
        fork();
        
    }
    
    printf("Hello world!");


}