#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    Node** adj;
} Graph;

Node* newNode(int v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->vertex = v;
    n->next = NULL;
    return n;
}

Graph* createGraph(int V) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->adj = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++)
        g->adj[i] = NULL;
    return g;
}

void addEdge(Graph* g, int src, int dest) {
    Node* n = newNode(dest);
    n->next = g->adj[src];
    g->adj[src] = n;
}

void BFS(Graph* g, int start) {
    int* visited = (int*)calloc(g->V, sizeof(int));
    int* queue = (int*)malloc(g->V * sizeof(int));
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        printf("%d ", u);
        Node* temp = g->adj[u];
        while (temp) {
            int v = temp->vertex;
            if (!visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}

int main() {
    int V = 6;
    Graph* g = createGraph(V);

    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    addEdge(g, 2, 4);
    addEdge(g, 3, 5);
    addEdge(g, 4, 5);

    BFS(g, 0);

    return 0;
}