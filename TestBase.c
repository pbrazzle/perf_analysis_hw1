#include "MeasureFunction.h"
#include "TopologicalSortAI.c"

// Main function to demonstrate the usage
int main() {
    Graph g;
    int vertices = 6;  // Number of vertices in the graph
    
    initializeGraph(&g, vertices);
    
    // Adding edges to the graph
    addEdge(&g, 5, 2);
    addEdge(&g, 5, 0);
    addEdge(&g, 4, 0);
    addEdge(&g, 4, 1);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 1);
    
    printf("Topological Sort of the given graph:\n");
    topologicalSort(&g);
    
    return 0;
}