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
    const int NUM_TESTS = 6;
    const int ITERATIONS = 100;
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
    /**
     * Test 1: test(small arr size, small subarr)
     * Test 2: test(small arr size, large subarr)
     * Test 3: test(med arr size, small subarr)
     * Test 4: test(med arr size, large subarr)
     * Test 5: test(large arr size, small subarr)
     * Test 6: test(large arr size, large subarr)
    */
    for(i = 0; i < ITERATIONS; i++) {
        timeArr[0][i] = test(250, 50);
        timeArr[1][i] = test(250, 250);
        timeArr[2][i] = test(2000, 50);
        timeArr[3][i] = test(2000, 250);
        timeArr[4][i] = test(20000, 50);
        timeArr[5][i] = test(20000, 250);
    }
    
    for(i = 0; i < NUM_TESTS; i++) {
        printf("Test Case %d:\n", i+1);
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