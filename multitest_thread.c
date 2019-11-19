#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct _SearchParams {
    int target;
    int* list;
    int start;
    int end;
} SearchParams;

void genParams(SearchParams*, int, int);

// this file is for multithread
int startSearch(int target, int* list, int size, int subArraySize) {
    pthread_t tid; // current thread
    pthread_t* threadArr; // array of all threads
    int i; // for loop control
    int threadNum; // total number of threads to be generated
    int* startIndices; // all start indices in list for threads
    int* endIndices; // all end indices in list for threads
    SearchParams params;

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

    // Allocate memory for arrays
    threadArr = (pthread_t*)calloc(threadNum, sizeof(pthread_t));
    startIndices = (int*)calloc(threadNum, sizeof(int));
    endIndices = (int*)calloc(threadNum, sizeof(int));

    // set all indices for searching
    for(i = 0; i < threadNum; i++) {
        startIndices[i] = i * subArraySize;
        endIndices[i] = i * subArraySize - 1;
        printf("threadNum:%d\n", threadNum);
        if(i == threadNum - 1) {
            endIndices[i] = size - 1;
        }
    }

    // create threads
    params.target = target;
    params.list = list;
    for(i = 0; i < threadNum; i++) {
        genParams(&params, startIndices[i], endIndices[i]);
        pthread_create(&tid, NULL, search, (void*)&params);
        threadArr[i] = tid;
    }

    // TODO: More thread wizardry and closing everything up

    /*
     * FREE params
     * FREE threadArr
     * FREE startIndices
     * FREE endIndices 
    */
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
    int* indexPtr = (int*)malloc(sizeof(int));

    for(i = seqSearchParams -> start; i <= seqSearchParams -> end; i++)
    {
        if(seqSearchParams -> list[i] == seqSearchParams -> target)
        {
            printf("found\n");
            indexPtr[0] = i;
            return (void*)indexPtr;
        }
    }

    indexPtr[0] = -1;
    return (void*)indexPtr;
}