/*
*   Speed optimized C implementation of Kahn's algorithm
*   Written by ChatGPT-4o mini
*
*   --- Prompt: Can you optimize the speed of this code? (after generating TopologicalSortAI.c)
*
*   --- ChatGPT Output:
*
*   Certainly! 
*   To optimize the speed of the topological sort implementation using Kahn's Algorithm, you can make several improvements:
*
*   1. Use Dynamic Data Structures: Instead of using fixed-size arrays for the queue and adjacency matrix, use dynamic data structures such as linked lists and dynamic arrays. 
*       This approach can be more efficient in terms of memory usage and avoids the overhead of managing large fixed-size arrays.
*    
*   2. Optimize Queue Operations: Use a circular queue to make enqueue and dequeue operations more efficient.
*    
*   3. Reduce Redundant Operations: Optimize the calculation of in-degrees and processing of vertices to reduce redundant operations.

*   Here’s an optimized version of the previous implementation that uses dynamic data structures and a more efficient queue implementation:
*
*   [code]
*
*   Key Improvements:
*
*   1. Dynamic Graph Representation: Uses adjacency lists instead of a fixed-size adjacency matrix. This is more memory-efficient, especially for sparse graphs.
*   2. Dynamic Queue Implementation: A custom queue implementation with linked list nodes improves efficiency for enqueue and dequeue operations.
*   3. Memory Management: Frees allocated memory to avoid leaks, ensuring that the program does not consume unnecessary memory.
*
*   This implementation should be more efficient, especially for larger and sparser graphs, 
*   as it avoids the overhead of a large adjacency matrix and uses a more dynamic approach for managing edges and vertices.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

typedef struct Graph {
    int numVertices;
    int *inDegree;
    Node **adjList;
} Graph;

Queue* createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, int vertex) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    
    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        return -1; // Indicates an empty queue
    }
    
    Node *temp = q->front;
    int vertex = temp->vertex;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return vertex;
}

Graph* createGraph(int vertices) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->numVertices = vertices;
    g->inDegree = (int *)calloc(vertices, sizeof(int));
    g->adjList = (Node **)malloc(vertices * sizeof(Node *));
    
    for (int i = 0; i < vertices; i++) {
        g->adjList[i] = NULL;
    }
    
    return g;
}

void addEdge(Graph *g, int src, int dest) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
    
    g->inDegree[dest]++;
}

void topologicalSort(Graph *g) {
    Queue *q = createQueue();
    
    // Enqueue all vertices with in-degree 0
    for (int i = 0; i < g->numVertices; i++) {
        if (g->inDegree[i] == 0) {
            enqueue(q, i);
        }
    }
    
    int visitedCount = 0;
    while (!isQueueEmpty(q)) {
        int u = dequeue(q);
        printf("%d ", u);
        visitedCount++;
        
        Node *temp = g->adjList[u];
        while (temp) {
            int v = temp->vertex;
            g->inDegree[v]--;
            
            if (g->inDegree[v] == 0) {
                enqueue(q, v);
            }
            
            temp = temp->next;
        }
    }
    
    if (visitedCount != g->numVertices) {
        printf("\nThe graph contains a cycle\n");
    } else {
        printf("\nTopological sort completed\n");
    }
    
    free(q);
}

/*
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
}*/