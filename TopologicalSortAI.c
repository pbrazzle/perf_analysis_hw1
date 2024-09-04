/*
C implementation of Kahn's algorithm
Written by ChatGPT 9/4/2024
    No previous chat history, no account

---ChatGPT Prompt---

Provide an implementation of Kahn's algorithm in C

---ChatGPT Text Output---

Kahn's algorithm is used for topological sorting of a directed acyclic graph (DAG). 
The algorithm works by maintaining a list of nodes with no incoming edges (nodes with in-degree 0). 
It repeatedly removes these nodes from the graph and updates the in-degree of their neighbors. 
If the graph is a DAG, the algorithm will produce a valid topological ordering.

Here's an implementation of Kahn's algorithm in C:

Explanation:

    Initialization:
        initQueue initializes the queue used for processing nodes with in-degree 0.
        inDegree is an array that keeps track of the in-degrees of all vertices.

    In-Degree Calculation:
        We calculate the in-degree of each vertex by counting the number of incoming edges.

    Queue Management:
        Vertices with in-degree 0 are enqueued initially.

    Processing:
        The algorithm processes each vertex from the queue, updates the in-degrees of its neighbors, and enqueues neighbors whose in-degrees become 0.

    Cycle Detection:
        If the number of vertices processed is less than the total number of vertices, the graph contains a cycle.

    Output:
        If the graph is acyclic, the topological order is printed; otherwise, a cycle message is displayed.

This implementation assumes the graph is represented as an adjacency matrix. For larger graphs or different representations (like adjacency lists), adjustments would be needed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the maximum number of vertices
#define MAX_VERTICES 100

// Structure for a queue
typedef struct {
    int items[MAX_VERTICES];
    int front, rear;
} Queue;

// Function to initialize a queue
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

// Function to check if the queue is empty
bool isEmpty(Queue *q) {
    return q->front > q->rear;
}

// Function to add an element to the queue
void enqueue(Queue *q, int item) {
    q->items[++q->rear] = item;
}

// Function to remove an element from the queue
int dequeue(Queue *q) {
    return q->items[q->front++];
}

// Function to perform topological sort using Kahn's algorithm
void kahnTopologicalSort(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int inDegree[MAX_VERTICES] = {0};  // Array to store in-degrees of all vertices
    Queue q;
    initQueue(&q);
    
    // Calculate in-degrees of all vertices
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (graph[j][i]) {
                inDegree[i]++;
            }
        }
    }
    
    // Enqueue vertices with in-degree 0
    for (int i = 0; i < numVertices; i++) {
        if (inDegree[i] == 0) {
            enqueue(&q, i);
        }
    }
    
    // List to store the topological order
    int topologicalOrder[MAX_VERTICES];
    int index = 0;
    
    // Process the vertices
    while (!isEmpty(&q)) {
        int u = dequeue(&q);
        topologicalOrder[index++] = u;
        
        // Reduce in-degrees of adjacent vertices
        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v]) {
                if (--inDegree[v] == 0) {
                    enqueue(&q, v);
                }
            }
        }
    }
    
    // Check if there was a cycle
    if (index != numVertices) {
        printf("The graph contains a cycle.\n");
    } else {
        // Print the topological order
        printf("Topological Order:\n");
        for (int i = 0; i < numVertices; i++) {
            printf("%d ", topologicalOrder[i]);
        }
        printf("\n");
    }
}

int main() {
    // Example graph: 6 vertices, edges as follows
    // (0->1), (0->2), (1->3), (1->4), (2->4), (3->5), (4->5)
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};
    int numVertices = 6;

    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][3] = 1;
    graph[1][4] = 1;
    graph[2][4] = 1;
    graph[3][5] = 1;
    graph[4][5] = 1;
    
    kahnTopologicalSort(graph, numVertices);
    
    return 0;
}