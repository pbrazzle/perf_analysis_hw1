#include <time.h>

unsigned long int measureCPUTimeInMicroseconds(void (*func)());

unsigned long int* measureMultipleCPUTimeRuns(void (*func)(), unsigned int trials);

unsigned long int measureWallTimeInMicroseconds(void (*func)());

unsigned long int* measureMultipleWallTimeRuns(void (*func)(), unsigned int trials);