// this file is for multiprocessing
#include <stdlib.h>
#include <stdio.h>
#include <math.h>   
int start(int target, int* list, int size, int procNum) {
    int i;
    int pid;
    int *pidList = (int *) malloc(sizeof(int) * procNum);
    for(i = 0; i < procNum; i++) {
        pid = fork();
        int start;
        int end;
        if(pid == 0) { // if we're a child
            search(target, list, start, end);
            exit(0);
        } else { // if we're at the parent
            pidList[i] = pid;
        }
        printf("i = %d\n", i);
    }

    for(i = 0; i < procNum; i++) {
        waitpid(pidList[i]);
    }

}

int search(int target, int* list, int start, int end) {
    int i;
    for(i = start; i <= end; i++) {
        if(list[i] == target) {
            return i;
        }
    }
}
