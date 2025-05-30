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
    n = newNode(src);
    n->next = g->adj[dest];
    g->adj[dest] = n;
}

Node* removeEdge(Node** head, int v) {
    Node *temp = *head, *prev = NULL;
    while (temp) {
        if (temp->vertex == v) {
            if (prev) prev->next = temp->next;
            else *head = temp->next;
            free(temp);
            return NULL;
        }
        prev = temp;
        temp = temp->next;
    }
    return NULL;
}

void removeUndirectedEdge(Graph* g, int u, int v) {
    removeEdge(&g->adj[u], v);
    removeEdge(&g->adj[v], u);
}

void hierholzerUtil(Graph* g, int u, int* path, int* pathIndex) {
    while (g->adj[u]) {
        int v = g->adj[u]->vertex;
        removeUndirectedEdge(g, u, v);
        hierholzerUtil(g, v, path, pathIndex);
    }
    path[(*pathIndex)++] = u;
}

int main() {
    int V = 5;
    Graph* g = createGraph(V);
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 0, 3);
    addEdge(g, 3, 4);
    addEdge(g, 4, 0);

    int maxEdges = 2 * V;
    int* path = (int*)malloc(maxEdges * sizeof(int));
    int pathIndex = 0;

    hierholzerUtil(g, 0, path, &pathIndex);

    for (int i = pathIndex - 1; i >= 0; i--)
        printf("%d ", path[i]);
    printf("\n");

    free(path);
    return 0;
}