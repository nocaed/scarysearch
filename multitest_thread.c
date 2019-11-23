#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

// struct that holds parameters for an array search
typedef struct _SearchParams {
    int target;
    int subArraySize;
    int* list;
    int totalSize;
    int currentThread;
    int indx;
} SearchParams;  

void* search(void* args) { 
    // create a new struct to hold search parameters
    SearchParams* paramStruct = (SearchParams*) args;
    // store search parameters in variables
    int target = paramStruct->target;
    int* list = paramStruct->list;
    int subArraySize = paramStruct->subArraySize;
    int totalSize = paramStruct->totalSize;
    int currentThread = paramStruct->currentThread;
    int i;
    // search the list from the current index in the subarray to the last
    for (i = currentThread * subArraySize; i <= currentThread * subArraySize + subArraySize - 1; i++) {
        // return the index of the target if found
        if (list[i] == target) {
            paramStruct->indx = i;
            pthread_exit(paramStruct);
        }
        // exit the loop if the search is about to hit the end of the list
        if (i == totalSize - 1) {
            break;
        }
    }
    // exit the thread with the current parameter struct
    pthread_exit(paramStruct);
} 

// start the search
int startSearch(int target, int* list, int size, int subArraySize) {
    int i;
    int indx = -1;
    // calculate the number of threads
    int numThreads = size / subArraySize;
    // add another thread if the number of subarrays don't divide evenly into the total array size
    if(size % subArraySize == 0) {
        numThreads++;
    }

    pthread_t thread[numThreads]; // array of threads
    int indices[numThreads]; // array of indices
    SearchParams* params[numThreads]; // array of search parameters
    // set array of search parameters
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
    // create threads
    for (i = 0; i < numThreads; i++) { 
        pthread_create(&thread[i], NULL, search, (void*) params[i]); 
    }
    // create pointer for the result of the search
    void* result;
    // join threads, check if result of search is valid
    for (i = 0; i < numThreads; i++) {
        
        pthread_join(thread[i], &result);
        int realResult = (params[i])->indx;
        if (realResult > -1) {
            indx = realResult;
        }
    }
    // free parameter array
    for(i = 0; i < numThreads; i++) {
        free(params[i]);
    }
    // return the index of the target
    return indx; 
} 

// print that the program is in thread mode
void printType() {
    printf("-thread\n");
}