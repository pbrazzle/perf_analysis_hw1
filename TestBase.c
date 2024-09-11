#include "MeasureFunction.h"
#include "TopologicalSortAI.c"

Graph g;

void init() {
    int vertices = 10;  // Number of vertices in the graph
    initializeGraph(&g, vertices);

    // Adding edges to the graph
    while (vertices > 0) {
        // Spread out
        int i;
        for (i = 1; i <= 5; i++) {
            addEdge(&g, vertices-1, vertices-1-i);
            if (vertices-1-i == 0) return;
        }
        
        // Collapse in
        if (vertices-7 < 0) return;
        for (i = 1; i <= 5; i++) {
            addEdge(&g, vertices-1-i, vertices-7);
        }

        vertices -= 6;
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
    printf("Wall times\n");
    for (i = 0; i < 20; i++) {
        printf("%ld, ", wallTimes[i]);
    }
    printf("\nCPU times\n");
    for (i = 0; i < 20; i++) {
        printf("%ld, ", cpuTimes[i]);
    }
    printf("\n");
    
    return 0;
}