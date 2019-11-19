// this file is for multiprocessing
#include <stdlib.h>
#include <stdio.h>
#include <math.h>   
int startSearch(int target, int* list, int size, int subArraySize) {
    // Error messages
    if(subArraySize > size) {
        printf("Error, subarray size cannot be bigger than total size");
        return -1;
    }
    if(subArraySize> 250) {
        printf("Error: subarray size cannot be greater than 250");
        return -1;
    }
    // In this part we set the number of processes we will use
    int procNum;
    if(size % subArraySize == 0) {
        procNum = size / subArraySize; // if the array is divisble by the subarray size we can just divide
    } else { // but if it's not divisible we have to use one additional process!
        procNum = size / subArraySize;
        procNum++;
    }
    
    int i; // so that i dont have to keep declaring i :D

    int *pidList = (int *) malloc(sizeof(int) * procNum); // holds the pid's of all the processes we spawn
    int *startIndices = (int *) malloc(sizeof(int) * procNum); // holds the start indices for each process to start searching the array at
    int* endIndices = (int *) malloc(sizeof(int) * procNum); // does the above but with end indices 
    // This loop sets the start and end indices using math :D
    for(i = 0; i < procNum; i++) {
        startIndices[i] = i * subArraySize;
        endIndices[i] = i * subArraySize + subArraySize - 1;
        printf("procNum: %d", procNum);
        if(i == procNum - 1) { // if we're at the last process
            endIndices[i] = size - 1; // the end index is just the last index of the array
        }
        printf("start index: %d, end index: %d\n", startIndices[i], endIndices[i]);
    }
    // This is the part where we fork :D
    for(i = 0; i < procNum; i++) {
        int pid = fork();
        int start = startIndices[i];
        int end = endIndices[i];
        if(pid == 0) { // if we're a child
            int indx = search(target, list, start, end); // only children search
            exit(indx);
        } else { // if we're at the parent
            pidList[i] = pid; // keep track of the pids of all the children!
        }
    }
    int status;
    int targetIndx = -1;
    // This is where the parent waits on the children
    for(i = 0; i < procNum; i++) {
 //       printf("pid: %d ", pidList[i]);
        waitpid(pidList[i], &status, 0);
        if(WEXITSTATUS(status) <= 250) {
            targetIndx = WEXITSTATUS(status); // target has been found
        }
//        printf("status: %d\n", WEXITSTATUS(status));
    }
    return targetIndx;
}
/**
 * This is just a sequential search that returns the index of the target
 */
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
