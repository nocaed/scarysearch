#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

double firstTest(int); // varies array length
double secondTest(int); // varies target
double thirdTest(int); // varies subarray size
int genRandomIntByRange(int upper, int lower);
double elapsedTimeInMilli(struct timeval* start, struct timeval* end); // gets elapsed time in milliseconds
// implements both process and thread techniques
int main() {
    // Set up
    srand(time(0));
    const int NUM_TESTS = 3;
    double** timeArr = (double**)calloc(NUM_TESTS, sizeof(double*));
    int i;
    int j;
    for(i = 0; i < NUM_TESTS; i++) {
        timeArr[i] = (double*)calloc(100, sizeof(double));
    }
    double avg = 0.0;
    // Testing
    for(i = 0; i < 100; i++) {
        timeArr[0][i] = firstTest(i);
        timeArr[1][i] = secondTest(i);
        timeArr[2][i] = thirdTest(i);
    }

    // TODO: CALCULATE STANDARD DEVIATION FOR EACH TEST CASE
    for(i = 0; i < NUM_TESTS; i++) {
        for(j = 0; j < 100; j++) {
            avg += timeArr[i][j];
        }
        avg /= 100;
        printf("The average runtime for test case %d was %f ms.\n", i + 1, avg);
        avg = 0.0;
    }
    
    for(i = 0; i < NUM_TESTS; i++) {
        free(timeArr[i]);
    }
    free(timeArr);

    return 0;
}

int* generateList(int size) {
    int i;
    int* list = (int*) malloc(sizeof(int) * size);
    for(i = 0; i < size; i++) {
        list[i] = i + 1;
    }
    return list;
}

void shuffleList(int* list, int size) {
    int i;
    int lower = 0;
    int upper = size - 1;
    for(i = 0; i < size; i++) {
        int rand1 = rand() % (upper - lower + 1);
        int rand2 = rand() % (upper - lower + 1);

        int temp;
        // the swap
        temp = list[rand1];
        list[rand1] = list[rand2];
        list[rand2] = temp;
    }
}

void printList(int* list, int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("%d, ", list[i]);
    }
    printf("\n");
}

void swapTarget(int *list, int size, int indx) {
    int lower = 0;
    int upper = size - 1;
    int temp;
    int random = rand() % (upper - lower + 1);
    temp = list[indx];
    list[indx] = list[random];
    list[random] = temp;
}

double firstTest(int i) {
    struct timeval start, end;
    int target;
    int index;
    int subArraySize;
    int size;
    int* list;

    gettimeofday(&start, NULL);
    target = 5;
    subArraySize = 4;
    size = genRandomIntByRange(1, 250 * 150);
    list = generateList(size);
    shuffleList(list, size);
    if(i == 0) {
        index = search(target, list, size, subArraySize, 0);
    }
    else {
        index = search(target, list, size, subArraySize, 1);
    }

    if(index == -1) {
        printf("Target (%d) was not found.\n", target);
    }
    else {
        printf("Target (%d) has been found at index %d.\n", target, index);
    }
    free(list);
    gettimeofday(&end, NULL);

    return elapsedTimeInMilli(&start, &end);
}

double secondTest(int i) {
    struct timeval start, end;
    int size;
    int subArraySize;
    int target;
    int* list;
    int index;

    gettimeofday(&start, NULL);
    subArraySize = 4;
    size = 37500;
    target = genRandomIntByRange(1, size);
    list = generateList(size);
    shuffleList(list, size);
    if(i == 0) {
        index = search(target, list, size, subArraySize, 0);
    }
    else {
        index = search(target, list, size, subArraySize, 1);
    }
    if(index == -1) {
        printf("Target (%d) was not found.\n", target);
    }
    else {
        printf("Target (%d) has been found at index %d.\n", target, index);
    }
    free(list);
    gettimeofday(&end, NULL);

    return elapsedTimeInMilli(&start, &end);
}

double thirdTest(int i) {
    struct timeval start, end;
    int target;
    int index;
    int subArraySize;
    int size;
    int* list;

    gettimeofday(&start, NULL);
    size = 37500;
    target = 5;
    subArraySize = genRandomIntByRange(1, 4);
    list = generateList(size);
    shuffleList(list, size);
    if(i == 0) {
        index = search(target, list, size, subArraySize, 0);
    }
    else {
        index = search(target, list, size, subArraySize, 1);
    }
    if(index == -1) {
        printf("Target (%d) was not found.\n", target);
    }
    else {
        printf("Target (%d) has been found at index %d.\n", target, index);
    }
    free(list);
    gettimeofday(&end, NULL);

    return elapsedTimeInMilli(&start, &end);
}

double elapsedTimeInMilli(struct timeval* start, struct timeval* end) {
    long secs, usecs;
    double meantime;

    secs = end -> tv_sec - start -> tv_sec;
    usecs = end -> tv_usec - start -> tv_usec;

    meantime = ((double)secs * 1000.0 + (double)usecs/1000.0);

    return meantime;
}

int genRandomIntByRange(int lower, int upper) {
    int randNum = rand() % (upper - lower + 1) + lower;
    
    return randNum;
}