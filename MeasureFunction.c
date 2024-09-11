#include "MeasureFunction.h"

unsigned int clockTimeToMilliseconds(clock_t clockTime) {
    return 1000 * clockTime / CLOCKS_PER_SEC;
}

unsigned int measureTimeInMilliseconds(void (*func)()) {
    clock_t start, end;
    
    start = clock();
    func();
    end = clock();

    return clockTimeToMilliseconds(end - start);
}

unsigned int* measureMultipleRuns(void (*func)(), unsigned int trials) {
    unsigned int* times = (unsigned int*) malloc(trials * sizeof(unsigned int));

    for (int i = 0; i < trials; ++i) {
        times[i] = measureTimeInMilliseconds(func);
    }

    return times;
}