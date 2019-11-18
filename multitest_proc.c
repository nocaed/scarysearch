// this file is for multiprocessing
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int start(int target, int* list, int size, int procNum) {
    int i;
    int procExp = (int) log2(procNum);
    int pid;
    int *pidList = (int *) malloc(sizeof(int) * procNum);
    for(i = 0; i < procNum; i++) {
        pid = fork();
        if(pid == 0) { // if we're at the parent
            printf("im gonna search :D\n");
            exit(0);
        } else {
            pidList[i] = pid;
        }
        printf("i = %d\n", i);
    }

    for(i = 0; i < procNum; i++) {
        waitpid(pidList[i]);
    }

}
