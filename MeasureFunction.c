#include "MeasureFunction.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#define _POSIX_C_SOURCE 200809L

struct timespec timespecDiff(struct timespec t1, struct timespec t2) {
    struct timespec diff;

    if (t2.tv_nsec < t1.tv_nsec) {
        t2.tv_nsec += 1000000000;
        t2.tv_sec--;
    }

    diff.tv_sec = t2.tv_sec - t1.tv_sec;
    diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;

    return diff;
}

unsigned long int measureCPUTimeInMicroseconds(void (*func)()) {
    struct timespec start, end;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    func();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    struct timespec diff = timespecDiff(start, end);

    return (diff.tv_sec * 1000000) + (diff.tv_nsec / 1000);
}

unsigned long int measureWallTimeInMicroseconds(void (*func)()) {
    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);
    func();
    clock_gettime(CLOCK_REALTIME, &end);

    struct timespec diff = timespecDiff(start, end);

    return (diff.tv_sec * 1000000) + (diff.tv_nsec / 1000);
}

unsigned long int* measureMultipleCPUTimeRuns(void (*func)(), unsigned int trials) {
    unsigned long int* times = (unsigned long int*) malloc(trials * sizeof(unsigned long int));

    int i = 0;
    for (i = 0; i < trials; ++i) {
        times[i] = measureCPUTimeInMicroseconds(func);
    }

    return times;
}

unsigned long int* measureMultipleWallTimeRuns(void (*func)(), unsigned int trials) {
    unsigned long int* times = (unsigned long int*) malloc(trials * sizeof(unsigned long int));

    int i = 0;
    for (i = 0; i < trials; ++i) {
        times[i] = measureWallTimeInMicroseconds(func);
    }

    return times;
}