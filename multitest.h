// header file with a macro to replace dummy search function in searchtest.c
#define search(x, y, z, a) startSearch(x, y, z, a) 


int startSearch(int, int*, int, int);

int* generateList(int size);

void printList(int* list, int size);

void shuffleList(int* list, int size);

void swapTarget(int*, int, int);

void setIndices(int *startIndices, int* endIndices, int procNum, int subArraySize, int size);

void printType();