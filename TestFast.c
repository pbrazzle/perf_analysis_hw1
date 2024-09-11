#include "MeasureFunction.h"
#include "TopologicalSortAIFast.c"

Graph* g;
int vertices = 200;

void init() {
    g = createGraph(vertices);

    // Adding edges to the graph
    while (vertices > 0) {
        // Spread out
        int i;
        for (i = 1; i <= 5; i++) {
            addEdge(g, vertices-1, vertices-1-i);
            if (vertices-1-i == 0) return;
        }
        
        // Collapse in
        if (vertices-7 < 0) return;
        for (i = 1; i <= 5; i++) {
            addEdge(g, vertices-1-i, vertices-7);
        }

        vertices -= 6;
    }
}

void refreshForList(Graph* g, int list) {
    Node* n = g->adjList[list];
    while (n) {
        g->inDegree[n->vertex]++;
        n = n->next;
    }
}

void refreshInDegree(Graph* g) {
    int i;
    for (i = 0; i < g->numVertices; i++) {
        g->inDegree[i] = 0;
    }

    for (i = 0; i < g->numVertices; i++) {
        refreshForList(g, i);
    }
}

void sort() {
    topologicalSort(g);
}

unsigned long int* wallTimes;
unsigned long int* cpuTimes;

void measureRuns() {
    wallTimes = (unsigned long int*) malloc(20 * sizeof(unsigned long int*));
    cpuTimes = (unsigned long int*) malloc(20 * sizeof(unsigned long int*));

    int i;
    for (i = 0; i < 20; i++) {
        wallTimes[i] = measureWallTimeInMicroseconds(&sort);
        refreshInDegree(g);
        cpuTimes[i] = measureCPUTimeInMicroseconds(&sort);
        refreshInDegree(g);
    }
}

// Main function to demonstrate the usage
int main() {
    init();

    measureRuns();

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