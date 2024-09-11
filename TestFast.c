#include "MeasureFunction.h"
#include "TopologicalSortAIFast.c"

int main() {
    int vertices = 6;
    Graph *g = createGraph(vertices);
    
    // Adding edges to the graph
    addEdge(g, 5, 2);
    addEdge(g, 5, 0);
    addEdge(g, 4, 0);
    addEdge(g, 4, 1);
    addEdge(g, 2, 3);
    addEdge(g, 3, 1);
    
    printf("Topological Sort of the given graph:\n");
    topologicalSort(g);
    
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
    
    return 0;
}