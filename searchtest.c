#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

double test(int, int);
void printTime(double**, int, int);
void printTestDetails(int);
int genRandomIntByRange(int upper, int lower);
double elapsedTimeInMilli(struct timeval* start, struct timeval* end); // gets elapsed time in milliseconds

int main() {
    printType();
    srand(time(0));
    const int NUM_TESTS = 13;
    const int ITERATIONS = 50;
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
        // first batch
        timeArr[0][i] = test(250, 250);
        timeArr[1][i] = test(500, 250);
        timeArr[2][i] = test(1000, 250);
        timeArr[3][i] = test(2000, 250);
        timeArr[4][i] = test(4000, 250);
        timeArr[5][i] = test(8000, 250);
        timeArr[6][i] = test(16000, 250);
        timeArr[7][i] = test(20000, 250);
        // second batch
        timeArr[8][i] = test(2000, 16);
        timeArr[9][i] = test(2000, 32);
        timeArr[10][i] = test(2000, 64);
        timeArr[11][i] = test(2000, 128);
        timeArr[12][i] = test(2000, 250);
    }

    for(i = 0; i < NUM_TESTS; i++) {
        printf("Test Case %d:\n", i+1);
        printf("Test Parameters: ");
        printTestDetails(i);
        printTime(timeArr, i, ITERATIONS);
        printf("\n");
    }
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

void printTime(double** timeArr, int testNum, int ITERATIONS) {
    int i, j;
    for(i = 0; i < ITERATIONS; i++) {
        printf("%f ", timeArr[testNum][i]);
    }
}

void printTestDetails(int testNum) {
    int arrSize;
    int subArrSize;

    switch(testNum) {
        case 0:
            arrSize = 250;
            subArrSize = 250;
            break;
        case 1:
            arrSize = 500;
            subArrSize = 250;
            break;

        case 2:
            arrSize = 1000;
            subArrSize = 250;
            break;
        case 3:
            arrSize = 2000;
            subArrSize = 250;
            break;
        case 4:
            arrSize = 4000;
            subArrSize = 250;
            break;
        case 5:
            arrSize = 8000;
            subArrSize = 250;
            break;
        case 6:
            arrSize = 16000;
            subArrSize = 250;
            break;
        case 7:
            arrSize = 20000;
            subArrSize = 250;
            break;
        case 8:
            arrSize = 2000;
            subArrSize = 16;
            break;
        case 9:
            arrSize = 2000;
            subArrSize = 32;
            break;
        case 10:
            arrSize = 2000;
            subArrSize = 64;
            break;
        case 11:
            arrSize = 2000;
            subArrSize = 128;
            break;
        case 12:
            arrSize = 2000;
            subArrSize = 250;
            break;
        default:
            arrSize = -1;
            subArrSize = -1;
            break;
    }

    printf("Searches an array of size %d for the number 5, with %d subarrays.\n", arrSize, subArrSize);
}