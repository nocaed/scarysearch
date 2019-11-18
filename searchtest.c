#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// implements both process and thread techniques
int main() {
    srand(time(NULL));
    int* list;
    int size = 25;
    list = generateList(size);
    printList(list, size);
    shuffleList(list, size);
    printList(list, size);
    test(3, list, size);
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