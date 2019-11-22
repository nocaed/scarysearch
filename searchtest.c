#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

double firstTest(int); // varies array length
double secondTest(); // varies target
double thirdTest(); // varies subarray size
double test(int, int);
int genRandomIntByRange(int upper, int lower);
double elapsedTimeInMilli(struct timeval* start, struct timeval* end); // gets elapsed time in milliseconds
// implements both process and thread techniques
int sequentialSearch(int* list, int size, int target) {
    int i;
    for(i = 0; i < size; i++) {
        if(list[i] == target) {
            return i;
        }
    }
    return -1;
}
int main() {
    // srand(time(0));
    // int size = 20;
    // int subArraySize = 5;
    // int target = 5;
    // int* list = generateList(size);
    // shuffleList(list, size);
    // int actualLocation = sequentialSearch(list, size, target);
    // printf("Actual loc: %d\n", actualLocation);
    // int indx = search(5, list, size, subArraySize, 0);
    // printf("We found it at %d with threads\n", indx);
    // Set up
    printType();
    srand(time(0));
    const int NUM_TESTS = 6;
    const int ITERATIONS = 5;
    double** timeArr = (double**)calloc(NUM_TESTS, sizeof(double*));
    int i;
    int j;
    double standardDeviation = 0.0;
    double max;
    double min;
    for(i = 0; i < NUM_TESTS; i++) {
        timeArr[i] = (double*)calloc(ITERATIONS, sizeof(double));
    }
    double avg = 0.0;
    // Testing
    for(i = 0; i < ITERATIONS; i++) {
        timeArr[0][i] = test(2000, 250);
        printf("%f ", timeArr[0][i]);
    }
    printf("\n");
    for(i = 0; i < ITERATIONS; i++) {
        timeArr[1][i] = test(20000, 250);
        printf("%f ", timeArr[1][i]);
    }
    printf("\n");
    for(i = 0; i < ITERATIONS; i++) {
        timeArr[2][i] = test(250, 250);
        printf("%f ", timeArr[2][i]);
    }
    printf("\n");
    for(i = 0; i < ITERATIONS; i++) {
        timeArr[3][i] = test(250, 250);
        printf("%f ", timeArr[3][i]);
    }
    printf("\n");
        for(i = 0; i < ITERATIONS; i++) {
        timeArr[4][i] = test(250, 1);
        printf("%f ", timeArr[4][i]);
    }
    for(i = 0; i < ITERATIONS; i++) {
        timeArr[5][i] = test(2000, 15);
        printf("%f ", timeArr[5][i]);
    }
    printf("\n");
    printf("\n");
    // calculate statistics
    for(i = 0; i < NUM_TESTS; i++) {
        for(j = 0; j < ITERATIONS; j++) {
            if(j == 0) {
                min = timeArr[i][j];
                max = timeArr[i][j];
            }
            else {
                if(timeArr[i][j] > max) {
                    max = timeArr[i][j];
                }
                if(timeArr[i][j] < min) {
                    min = timeArr[i][j];
                }
            }
            avg += timeArr[i][j];
        }
        printf("The minimum runtime for test case %d was %f ms.\n", i+1, min);
        printf("The maximum runtime for test case %d was %f ms.\n", i+1, max);
        avg /= ITERATIONS;
        printf("The average runtime for test case %d was %f ms.\n", i+1, avg);
        for(j = 0; j < ITERATIONS; j++) {
            standardDeviation += pow(timeArr[i][j] - avg, 2.0);
        }
        standardDeviation /= ITERATIONS;
        standardDeviation = sqrt(standardDeviation);
        printf("The standard deviation for test case %d was %f ms.\n\n", i+1, standardDeviation);
        avg = 0.0;
        standardDeviation = 0.0;
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
    subArraySize = 250;
    size = 2500;
    list = generateList(size);
    shuffleList(list, size);
    if(i == 0) {
        index = search(target, list, size, subArraySize);
    }
    else {
        index = search(target, list, size, subArraySize);
    }

    if(index == -1) {
        printf("Target (%d) was not found.\n", target);
    }
    else {
    //    printf("Target (%d) has been found at index %d.\n", target, index);
    }
    free(list);
    gettimeofday(&end, NULL);

    return elapsedTimeInMilli(&start, &end);
}

double secondTest() {
    struct timeval start, end;
    int size;
    int subArraySize;
    int target;
    int* list;
    int index;

    gettimeofday(&start, NULL);
    subArraySize = 250;
    size = 5000;
    target = 5;
    list = generateList(size);
    shuffleList(list, size);
    index = search(target, list, size, subArraySize);
    if(index == -1) {
        printf("Target (%d) was not found.\n", target);
    }
    else {
    //    printf("Target (%d) has been found at index %d.\n", target, index);
    }
    free(list);
    gettimeofday(&end, NULL);

    return elapsedTimeInMilli(&start, &end);
}

double thirdTest() {
    struct timeval start, end;
    int target;
    int index;
    int subArraySize;
    int size;
    int* list;

    gettimeofday(&start, NULL);
    size = 37500;
    target = 5;
    subArraySize = 250;
    list = generateList(size);
    shuffleList(list, size);
    index = search(target, list, size, subArraySize);
    if(index == -1) {
        printf("Target (%d) was not found.\n", target);
    }
    else {
    //    printf("Target (%d) has been found at index %d.\n", target, index);
    }
    free(list);
    gettimeofday(&end, NULL);

    return elapsedTimeInMilli(&start, &end);
}

double test(int arraySize, int subArraySize) {
    struct timeval start, end;
    int target;
    int index;
    int* list;

    gettimeofday(&start, NULL);
    target = 5;
    list = generateList(arraySize);
    shuffleList(list, arraySize);
    index = search(target, list, arraySize, subArraySize);
    if(index == -1) {
        printf("Target (%d) was not found.\n", target);
    }
    else {
    //    printf("Target (%d) has been found at index %d.\n", target, index);
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