#include "MeasureFunction.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#define _POSIX_C_SOURCE 200809L

unsigned int clockTimeToMilliseconds(clock_t clockTime) {
    return 1000 * clockTime / CLOCKS_PER_SEC;
}

unsigned int measureTimeInMilliseconds(void (*func)()) {
    clock_t start, end;
    
    start = clock();
    func();
    end = clock();

    printf("Clock_t time start: %ld\n", start);
    printf("Clock_t time end: %ld\n", end);

    return clockTimeToMilliseconds(end - start);
}

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

unsigned int measureWallTimeInMilliseconds(void (*func)()) {
    struct timespec start, end;

    start = clock_gettime(CLOCK_REALTIME, &start);
    func();
    end = clock_gettime(CLOCK_REALTIME, &end);

    struct timespec diff = timespecDiff(start, end);
    printf("Took %jd seconds, %09ld ns\n", (intmax_t)diff.tv_sec, diff.tv_nsec);

    return 0;
}

unsigned int* measureMultipleRuns(void (*func)(), unsigned int trials) {
    unsigned int* times = (unsigned int*) malloc(trials * sizeof(unsigned int));

    int i = 0;
    for (i = 0; i < trials; ++i) {
        times[i] = measureTimeInMilliseconds(func);
    }

    return times;
}