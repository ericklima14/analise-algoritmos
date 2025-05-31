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

int isBipartite(Graph* g) {
    int* color = (int*)malloc(g->V * sizeof(int));
    for (int i = 0; i < g->V; i++)
        color[i] = -1;

    int* queue = (int*)malloc(g->V * sizeof(int));

    for (int start = 0; start < g->V; start++) {
        if (color[start] == -1) {
            color[start] = 0;
            int front = 0, rear = 0;
            queue[rear++] = start;

            while (front < rear) {
                int u = queue[front++];
                Node* temp = g->adj[u];
                while (temp) {
                    int v = temp->vertex;
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        queue[rear++] = v;
                    } else if (color[v] == color[u]) {
                        free(color);
                        free(queue);
                        return 0;
                    }
                    temp = temp->next;
                }
            }
        }
    }

    free(color);
    free(queue);
    return 1;
}

int main() {
    int V = 4;
    Graph* g = createGraph(V);
    addEdge(g, 0, 1);
    addEdge(g, 0, 3);
    addEdge(g, 1, 2);
    addEdge(g, 2, 3);

    if (isBipartite(g))
        printf("Bipartido\n");
    else
        printf("Nao bipartido\n");

    return 0;
}