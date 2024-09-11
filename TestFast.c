#include "MeasureFunction.h"
#include "TopologicalSortAIFast.c"

Graph* g;
int vertices = 6;

void init() {
    g = createGraph(vertices);

    // Adding edges to the graph
    int i;
    for (i = 0; i < 99; i++) {
        addEdge(g, i, i+1);
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
        refreshForList(i);
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
    for (i = 0; i < 20; i++) {
        printf("Run %d: Wall - %ld, CPU - %ld\n", i, wallTimes[i], cpuTimes[i]);
    }

    return 0;
}