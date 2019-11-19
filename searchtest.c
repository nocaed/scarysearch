#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
// implements both process and thread techniques
int main() {
    srand(time(NULL));
    int* list;
    int size = 249;
    list = generateList(size);
    shuffleList(list, size);
    int indx = test(3, list, size, 1);
    indx = test(3, list, size, 4);
//    printList(list, size);
    swapTarget(list, size, indx);
//    printList(list, size);
    free(list);
    return 0;
}

int* generateList(int size) {
    int i;
    int* list = (int*) malloc(sizeof(int) * size);
    for(i = 0; i < size; i++) {
        list[i] = i + 1;
    }
    return list;
}

void shuffleList(int* list, int size) {
    int i;
    int lower = 0;
    int upper = size - 1;
    for(i = 0; i < size; i++) {
        int rand1 = rand() % (upper - lower + 1);
        int rand2 = rand() % (upper - lower + 1);

        int temp;
        // the swap
        temp = list[rand1];
        list[rand1] = list[rand2];
        list[rand2] = temp;
    }
}

void printList(int* list, int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("%d, ", list[i]);
    }
    printf("\n");
}

void swapTarget(int *list, int size, int indx) {
    int lower = 0;
    int upper = size - 1;
    int temp;
    int random = rand() % (upper - lower + 1);
    temp = list[indx];
    list[indx] = list[random];
    list[random] = temp;
}

int runTest(int target, int *list, int size, int subArraySize) {
    int index = test(target, list, size, subArraySize);
    swapTarget(list, size, index);
    
}