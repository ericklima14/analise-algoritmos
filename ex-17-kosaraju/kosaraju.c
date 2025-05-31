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

void push(int* stack, int* top, int v) {
    stack[(*top)++] = v;
}

int pop(int* stack, int* top) {
    return stack[--(*top)];
}

void fillOrder(Graph* g, int v, int* visited, int* stack, int* top) {
    visited[v] = 1;
    Node* temp = g->adj[v];
    while (temp) {
        if (!visited[temp->vertex])
            fillOrder(g, temp->vertex, visited, stack, top);
        temp = temp->next;
    }
    push(stack, top, v);
}

Graph* transposeGraph(Graph* g) {
    Graph* gt = createGraph(g->V);
    for (int v = 0; v < g->V; v++) {
        Node* temp = g->adj[v];
        while (temp) {
            addEdge(gt, temp->vertex, v);
            temp = temp->next;
        }
    }
    return gt;
}

void DFSUtil(Graph* g, int v, int* visited) {
    visited[v] = 1;
    printf("%d ", v);
    Node* temp = g->adj[v];
    while (temp) {
        if (!visited[temp->vertex])
            DFSUtil(g, temp->vertex, visited);
        temp = temp->next;
    }
}

void kosaraju(Graph* g) {
    int V = g->V;
    int* visited = (int*)calloc(V, sizeof(int));
    int* stack = (int*)malloc(V * sizeof(int));
    int top = 0;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            fillOrder(g, i, visited, stack, &top);

    Graph* gt = transposeGraph(g);

    for (int i = 0; i < V; i++)
        visited[i] = 0;

    printf("Componentes fortemente conectados:\n");
    while (top) {
        int v = pop(stack, &top);
        if (!visited[v]) {
            DFSUtil(gt, v, visited);
            printf("\n");
        }
    }

    free(visited);
    free(stack);
    for (int i = 0; i < V; i++)
        free(gt->adj[i]);
    free(gt->adj);
    free(gt);
}

int main() {
    int V = 5;
    Graph* g = createGraph(V);
    addEdge(g, 1, 0);
    addEdge(g, 0, 2);
    addEdge(g, 2, 1);
    addEdge(g, 0, 3);
    addEdge(g, 3, 4);

    kosaraju(g);

    return 0;
}