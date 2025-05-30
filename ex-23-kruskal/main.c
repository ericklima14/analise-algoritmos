#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Graph {
    int V, E;
    Edge* edges;
} Graph;

Graph* createGraph(int V, int E) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->E = E;
    g->edges = (Edge*)malloc(E * sizeof(Edge));
    return g;
}

int compareEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

int find(int* parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void unionSets(int* parent, int* rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[yroot] < rank[xroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

void kruskalMST(Graph* g) {
    Edge* result = (Edge*)malloc(g->V * sizeof(Edge));
    int e = 0;
    int i = 0;

    qsort(g->edges, g->E, sizeof(Edge), compareEdges);

    int* parent = (int*)malloc(g->V * sizeof(int));
    int* rank = (int*)calloc(g->V, sizeof(int));

    for (int v = 0; v < g->V; v++)
        parent[v] = v;

    while (e < g->V - 1 && i < g->E) {
        Edge next_edge = g->edges[i++];
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            unionSets(parent, rank, x, y);
        }
    }

    printf("Arestas da MST:\n");
    for (i = 0; i < e; i++)
        printf("%d - %d : %d\n", result[i].src, result[i].dest, result[i].weight);

    free(result);
    free(parent);
    free(rank);
}

int main() {
    int V = 4;
    int E = 5;
    Graph* g = createGraph(V, E);

    g->edges[0].src = 0; g->edges[0].dest = 1; g->edges[0].weight = 10;
    g->edges[1].src = 0; g->edges[1].dest = 2; g->edges[1].weight = 6;
    g->edges[2].src = 0; g->edges[2].dest = 3; g->edges[2].weight = 5;
    g->edges[3].src = 1; g->edges[3].dest = 3; g->edges[3].weight = 15;
    g->edges[4].src = 2; g->edges[4].dest = 3; g->edges[4].weight = 4;

    kruskalMST(g);

    free(g->edges);
    free(g);

    return 0;
}