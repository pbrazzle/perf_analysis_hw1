#include "MeasureFunction.h"
#include "TopologicalSortAI.c"

Graph g;

void initializeGraph() {
    int vertices = 6;  // Number of vertices in the graph
    initializeGraph(&g, vertices);

    // Adding edges to the graph
    addEdge(&g, 5, 2);
    addEdge(&g, 5, 0);
    addEdge(&g, 4, 0);
    addEdge(&g, 4, 1);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 1);
}

void sort() {
    topologicalSort(&g);
}

// Main function to demonstrate the usage
int main() {
    printf("Topological Sort of the given graph:\n");
    unsigned int millis = measureTimeInMilliseconds(&sort);

    printf("Took %d miiliseconds\n", millis);
    
    return 0;
}