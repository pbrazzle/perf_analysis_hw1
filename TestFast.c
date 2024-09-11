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

void sort() {
    topologicalSort(g);
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
    
    /*
    // Free memory
    for (int i = 0; i < vertices; i++) {
        Node *temp = g->adjList[i];
        while (temp) {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    
    free(g->adjList);
    free(g->inDegree);
    free(g);
    */

    return 0;
}