#include "multitest.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

double test(int, int);
void printTime(double**, int, int);
void printTestDetails(int);
double elapsedTimeInMilli(struct timeval* start, struct timeval* end);

int main() {
    // print if the program has been compiled in process or thread
    printType();
    // seed the number randomizer
    srand(time(0));
    const int NUM_TESTS = 13; // number of tests to be run
    const int ITERATIONS = 50; // number of times each test will be run
    double** timeArr = (double**)calloc(NUM_TESTS, sizeof(double*)); // 2d array of elapsed time values in ms for each test case
    int i; // general/outer loop counter
    int j; // inner loop counter
    double standardDeviation = 0.0; // holds standard deviation of a test case
    double max; // holds the maximum runtime of a test case
    double min; // holds the minimum runtime of a test case
    // allocate memory for each iteration of a test case
    for(i = 0; i < NUM_TESTS; i++) {
        timeArr[i] = (double*)calloc(ITERATIONS, sizeof(double));
    }
    double avg = 0.0; // holds the mean runtime for each test case

    // Running test cases
    for(i = 0; i < ITERATIONS; i++) {
        // first batch, vary array sizes
        timeArr[0][i] = test(250, 250);
        timeArr[1][i] = test(500, 250);
        timeArr[2][i] = test(1000, 250);
        timeArr[3][i] = test(2000, 250);
        timeArr[4][i] = test(4000, 250);
        timeArr[5][i] = test(8000, 250);
        timeArr[6][i] = test(16000, 250);
        timeArr[7][i] = test(20000, 250);
        // second batch, vary subarray sizes
        timeArr[8][i] = test(2000, 16);
        timeArr[9][i] = test(2000, 32);
        timeArr[10][i] = test(2000, 64);
        timeArr[11][i] = test(2000, 128);
        timeArr[12][i] = test(2000, 250);
    }

    // Print specific details for each test case
    for(i = 0; i < NUM_TESTS; i++) {
        printf("Test Case %d:\n", i+1);
        printf("Test Parameters: ");
        printTestDetails(i);
        printTime(timeArr, i, ITERATIONS);
        printf("\n");
    }
    // Calculate statistics for each test case
    for(i = 0; i < NUM_TESTS; i++) {
        // Calculate min/max and get sum of runtimes
        for(j = 0; j < ITERATIONS; j++) {
            // if this is the first runtime, initialize min and max
            if(j == 0) {
                min = timeArr[i][j];
                max = timeArr[i][j];
            }
            // otherwise, check for new min/max values
            else {
                if(timeArr[i][j] > max) {
                    max = timeArr[i][j];
                }
                if(timeArr[i][j] < min) {
                    min = timeArr[i][j];
                }
            }
            // add to the sum of runtimes
            avg += timeArr[i][j];
        }
        // output the min/max runtimes
        printf("The minimum runtime for test case %d was %f ms.\n", i+1, min);
        printf("The maximum runtime for test case %d was %f ms.\n", i+1, max);
        // calculate the average
        avg /= ITERATIONS;
        // output the average
        printf("The average runtime for test case %d was %f ms.\n", i+1, avg);
        // calculate the standard deviation
        for(j = 0; j < ITERATIONS; j++) {
            standardDeviation += pow(timeArr[i][j] - avg, 2.0);
        }
        standardDeviation /= ITERATIONS;
        standardDeviation = sqrt(standardDeviation);
        // output the standard deviation
        printf("The standard deviation for test case %d was %f ms.\n\n", i+1, standardDeviation);
        // reset average and stdev
        avg = 0.0;
        standardDeviation = 0.0;
    }
    
    // free the memory taken up by the 2d array of runtimes
    for(i = 0; i < NUM_TESTS; i++) {
        free(timeArr[i]);
    }
    free(timeArr);

    return 0;
}

// generate a list of {size} bytes
int* generateList(int size) {
    int i;
    // allocate memory for the list of numbers
    int* list = (int*) malloc(sizeof(int) * size);
    // assign values to each index
    for(i = 0; i < size; i++) {
        list[i] = i + 1;
    }
    // return the list
    return list;
}

// shuffle a list of values
void shuffleList(int* list, int size) {
    int i;
    // the lowest value that can be randomly generated
    int lower = 0;
    // the highest value that can be randomly generated
    int upper = size - 1;
    // loop that shuffles the list at every index
    for(i = 0; i < size; i++) {
        // randomly choose indexes to swap
        int rand1 = rand() % (upper - lower + 1) + lower;
        int rand2 = rand() % (upper - lower + 1) + lower;

        int temp;
        // the swap
        temp = list[rand1];
        list[rand1] = list[rand2];
        list[rand2] = temp;
    }
}

// runs a search with an arraySize and a subArraySize
double test(int arraySize, int subArraySize) {
    struct timeval start, end; // hold a time snapshot
    int target; // the value to find
    int index; // the index that the target is at
    int* list; // the list to search

    // take snapshot of time of search start
    gettimeofday(&start, NULL);
    // set target
    target = 5;
    // generate a list of arraySize bytes
    list = generateList(arraySize);
    // shuffle the list
    shuffleList(list, arraySize);
    // search for the target
    index = search(target, list, arraySize, subArraySize);
    // error checking
    if(index == -1) {
        printf("Target (%d) was not found.\n", target);
    }
    // free the list
    free(list);
    // snapshot of runtime end
    gettimeofday(&end, NULL);

    // return the elapsed time
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

// print the runtime for every test case iteration
void printTime(double** timeArr, int testNum, int ITERATIONS) {
    int i, j;
    for(i = 0; i < ITERATIONS; i++) {
        if(i == ITERATIONS - 1) {
            printf("%f", timeArr[testNum][i]);
        }
        else {
            printf("%f, ", timeArr[testNum][i]);
        }
    }
}

// print the parameters of the test case
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