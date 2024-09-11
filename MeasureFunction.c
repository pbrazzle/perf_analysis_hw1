#include "MeasureFunction.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

unsigned int clockTimeToMilliseconds(clock_t clockTime) {
    return 1000 * clockTime / CLOCKS_PER_SEC;
}

unsigned int measureTimeInMilliseconds(void (*func)()) {
    clock_t start, end;
    
    start = clock();
    int dummy = 0;
    for (int i = 0; i < 1000000; i++) dummy += i;
    func();
    end = clock();

    printf("Clock_t time start: %ld\n", start);
    printf("Clock_t time end: %ld\n", end);

    return clockTimeToMilliseconds(end - start);
}

unsigned int* measureMultipleRuns(void (*func)(), unsigned int trials) {
    unsigned int* times = (unsigned int*) malloc(trials * sizeof(unsigned int));

    for (int i = 0; i < trials; ++i) {
        times[i] = measureTimeInMilliseconds(func);
    }

    return times;
}