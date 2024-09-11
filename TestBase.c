#include "MeasureFunction.h"
#include "TopologicalSortAI.c"

Graph g;

void init() {
    int vertices = 10;  // Number of vertices in the graph
    initializeGraph(&g, vertices);

    // Adding edges to the graph
    int i;
    for (i = 0; i < vertices-1; i++) {
        addEdge(&g, i, i+1);
    }
}

void sort() {
    topologicalSort(&g);
}

// Main function to demonstrate the usage
int main() {
    init();

    printf("Topological Sort of the given graph:\n");
    unsigned long int* wallTimes = measureMultipleWallTimeRuns(&sort, 20);
    unsigned long int* cpuTimes = measureMultipleCPUTimeRuns(&sort, 20);

    int i = 0;
    for (i = 0; i < 20; i++) {
        printf("Run %d: Wall - %ld, CPU - %ld\n", i, wallTimes[i], cpuTimes[i]);
    }
    
    return 0;
}