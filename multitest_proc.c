// this file is for multiprocessing
#include <stdlib.h>
#include <stdio.h>
#include <math.h>   
int start(int target, int* list, int size, int subArraySize) {
    if(subArraySize > size) {
        printf("Error, subarray size cannot be bigger than total size");
        return -1;
    }
    if(subArraySize> 250) {
        printf("Error: subarray size cannot be greater than 250");
        return -1;
    }
    int procNum;
    if(size % subArraySize == 0) {
        int procNum = size / subArraySize;
    } else {
        procNum = size / subArraySize;
        procNum++;
    }
    
    int i;
    int pid;
    int *pidList = (int *) malloc(sizeof(int) * procNum);
    int *startIndices = (int *) malloc(sizeof(int) * (size / subArraySize));
    int* endIndices = (int *) malloc(sizeof(int) * procNum);
    for(i = 0; i < procNum; i++) {
        startIndices[i] = i * subArraySize;
        endIndices[i] = i * subArraySize + subArraySize - 1;
        if(i == procNum - 1) {
            endIndices[i] = size - 1;
        }
        printf("start index: %d, end index: %d\n", startIndices[i], endIndices[i]);
    }
    for(i = 0; i < procNum; i++) {
        pid = fork();
        int start = 0;
        int end = size - 1;
        if(pid == 0) { // if we're a child
            int indx = search(target, list, start, end); //WEXITSTATUS(status)
            exit(indx);
        } else { // if we're at the parent
            pidList[i] = pid;
        }
    }
    int status;
    
    for(i = 0; i < procNum; i++) {
        printf("pid: %d ", pidList[i]);
        waitpid(pidList[i], &status, 0);
        printf("status: %d\n", WEXITSTATUS(status));
    }

}

int search(int target, int* list, int start, int end) {
    int i;
    for(i = start; i <= end; i++) {
        if(list[i] == target) {
            printf("found\n");
            return i;
        }
    }
    return -1;
}
