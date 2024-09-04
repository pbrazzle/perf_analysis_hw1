unsigned int clockTimeToMilliseconds(clock_t clockTime);

unsigned int measureTimeInMilliseconds(void (*func)());

unsigned int* measureMultipleRuns(void (*func)(), unsigned int trials);