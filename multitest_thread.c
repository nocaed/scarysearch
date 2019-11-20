#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

typedef struct _SearchParams {
    int target;
    int* list;
    int start;
    int end;
} SearchParams;

void* search(void*);
void setIndices(int*, int*, int, int, int);
void genParams(SearchParams*, int, int);

// this file is for multithread
int startSearch(int target, int* list, int size, int subArraySize) {
    printf("yeet");
    pthread_t tid; // current thread
    pthread_t* threadArr; // array of all threads
    int i; // for loop control
    int threadNum; // total number of threads to be generated
    int tIndex = -1; // index of target value
    void* status; // status of current thread
    int* startIndices; // all start indices in list for threads
    int* endIndices; // all end indices in list for threads
    SearchParams** paramList = (SearchParams**)malloc(sizeof(SearchParams) * threadNum); // search parameters that declare a sublist
    printf("CHECKPOINT 1");
    // error messages
    if(subArraySize > size) {
        // if subarray size is larger than the size of the list
        printf("Error, subarray size cannot be larger than total size.");
        return -1;
    }
    if(subArraySize > 250) {
        // if the subarray size is greater than the maximum subarray size
        printf("Error, subarray size cannot be larger than 250.");
        return -1;
    }

    // calculate the total number of threads
    threadNum = size / subArraySize;
    if(size % subArraySize != 0) {
        threadNum++;
    }
    printf("CHECKPOINT 2");
    // Allocate memory for arrays
    threadArr = (pthread_t*)calloc(threadNum, sizeof(pthread_t));
    startIndices = (int*)calloc(threadNum, sizeof(int));
    endIndices = (int*)calloc(threadNum, sizeof(int));
    printf("fuck this shit");
    // set all indices for searching
    setIndices(startIndices, endIndices, threadNum, subArraySize, size);
    printf("CHECKPOINT 3");
    // create threads
    for(i = 0; i < threadNum; i++) {
                // Correctly generate the parameters :D
        paramList[i] = (SearchParams*) malloc(sizeof(SearchParams)); // allocate space for the struct
        printf("CHECKPOINT 4");
        SearchParams* currentParams = paramList[i]; // a named variable for clarity! :D
        currentParams->target = target;
        currentParams->list = list;
        currentParams->start = startIndices[i];
        currentParams->end = endIndices[i];
        pthread_create(&tid, NULL, search, (void*)currentParams);
        threadArr[i] = tid;
    }
    
    // wait on threads
    int temp;
    for(i = 0; i < threadNum; i++)
    {
        pthread_join(threadArr[i], &status);
        temp = *((int*)status);
        if(temp > -1)
        {
            tIndex = temp;
        }
    }
    

    printf("Target found at index %d\n", tIndex);
    //free(params); TODO free paramList
    free(threadArr);
    free(startIndices);
    free(endIndices);
    return tIndex;
}

// sets start and end indices for the search parameters
void genParams(SearchParams* params, int start, int end) {
    params -> start = start;
    params -> end = end;
}

// Searches list of numbers for a target value
void* search(void* params) {
    SearchParams* seqSearchParams = (SearchParams*)params;
    int i;
    int* indexPtr = malloc(sizeof(int));
    int* searchList = seqSearchParams -> list;

    for(i = seqSearchParams -> start; i <= seqSearchParams -> end; i++)
    {
        printf("Index: %d\n", i);
        if(searchList[i] == seqSearchParams -> target)
        {
            printf("found\n");
            *(indexPtr) = i;
            pthread_exit((void*)indexPtr);
        }
    }

    *(indexPtr) = -1;
    pthread_exit((void*)indexPtr);
}

void setIndices(int *startIndices, int* endIndices, int procNum, int subArraySize, int size) {
    int i;
    for(i = 0; i < procNum; i++) {
        startIndices[i] = i * subArraySize;
        endIndices[i] = i * subArraySize + subArraySize - 1;
        if(i == procNum - 1) { // if we're at the last thread
            endIndices[i] = size - 1; // the end index is just the last index of the array
        }
    }
}