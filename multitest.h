// header file with a macro to replace dummy search function in searchtest.c
#define test(x) search(x) 


int search(int target);

int* generateList(int size);

void printList(int* list, int size);

void shuffleList(int* list, int size);