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
int start(int target, int* list, int size, int threadNum) {
    pthread_t tid;
    int i;

    SearchParams* params = (SearchParams*)malloc(sizeof(SearchParams));
    params -> target = target;
    params -> list = list;
    params -> start = start;
    // TODO: ADD END TO PARAMS
    
}

void* search(void* params)
{

}