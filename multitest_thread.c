#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct _SearchParams
{
    int target;
    int* list;
    int start;
    int end;
} SearchParams;

// this file is for multithread
int startSearch(int target, int* list, int size, int subArraySize) {
    pthread_t tid;
    int i;
    // TODO: ADD START TO PARAMS
    // TODO: ADD END TO PARAMS
    // error messages
    if(subArraySize > size)
    {
        printf("Error, subarray size cannot be larger than total size.");
        return -1;
    }
    if(subArraySize > 250)
    {
        printf("Error, subarray size cannot be larger than 250.");
        return -1;
    }


    SearchParams* params = (SearchParams*)malloc(sizeof(SearchParams));
    params -> target = target;
    params -> list = list;
}

// Searches list of numbers for a target value
void* search(void* params)
{
    SearchParams* seqSearchParams = (SearchParams*)params;
    int i;
    void* indexPtr;
    int* errorNum = (int*)malloc(sizeof(int));
    errorNum[0] = -1;

    for(i = seqSearchParams -> start; i <= seqSearchParams -> end; i++)
    {
        if(seqSearchParams -> list[i] == seqSearchParams -> target)
        {
            printf("found\n");
            indexPtr = seqSearchParams -> list[i];
            return indexPtr;
        }
    }

    indexPtr = (void*)errorNum;
    return indexPtr;
}