#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

typedef struct _SearchParams {
    int target;
    int subArraySize;
    int* list;
    int totalSize;
    int currentThread;
    int indx;
} SearchParams;  

void* search(void* args) { 
    SearchParams* paramStruct = (SearchParams*) args;
    int target = paramStruct->target;
    int* list = paramStruct->list;
    int subArraySize = paramStruct->subArraySize;
    int totalSize = paramStruct->totalSize;
    int currentThread = paramStruct->currentThread;
    int i;
    for (i = currentThread * subArraySize; i <= currentThread * subArraySize + subArraySize - 1; i++) {
        if (list[i] == target) {
            paramStruct->indx = i;
            pthread_exit(paramStruct);
        }
        if (i == totalSize - 1) {
            break;
        }
    }
    pthread_exit(paramStruct);
} 
  
int startSearch(int target, int* list, int size, int subArraySize, int timesRan) {
    int i;
    int indx = -1;
    int numThreads = size / subArraySize;
    if(size % subArraySize == 0) {
        numThreads++;
    }

    pthread_t thread[numThreads];
    int indices[numThreads];
    SearchParams* params[numThreads];
    for(i = 0; i < numThreads; i++) {
        SearchParams* parameters = (SearchParams*) malloc(sizeof(SearchParams));
        parameters->list = list;
        parameters->subArraySize = subArraySize;
        parameters->target = target;
        parameters->totalSize = size;
        parameters->currentThread = i;
        parameters->indx = -1;
        params[i] = parameters;
    }
    for (i = 0; i < numThreads; i++) { 
        pthread_create(&thread[i], NULL, search, (void*) params[i]); 
    }
    void* result;
    for (i = 0; i < numThreads; i++) {
        
        pthread_join(thread[i], &result);
        int realResult = (params[i])->indx;
        if (realResult > -1) {
            indx = realResult;
        }
    }
    for(i = 0; i < numThreads; i++) {
        free(params[i]);
    }
    return indx; 
} 
// int* generateList(int size) {
//     int i;
//     int* list = (int*) malloc(sizeof(int) * size);
//     for(i = 0; i < size; i++) {
//         list[i] = i + 1;
//     }
//     return list;
// }
// int main() {
//     int* list = generateList(2500);
//     int indx = startSearch(437, list, 2500, 250, 0);
//     printf("found at %d", indx);
// }