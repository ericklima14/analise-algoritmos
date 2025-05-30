#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Graph {
    int V, E;
    Edge* edges;
} Graph;

Graph* createGraph(int V, int E) {
    Graph* g = malloc(sizeof(Graph));
    g->V = V;
    g->E = E;
    g->edges = malloc(E * sizeof(Edge));
    return g;
}

void bellmanFord(Graph* g, int src) {
    int V = g->V;
    int E = g->E;
    int* dist = malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = g->edges[j].src;
            int v = g->edges[j].dest;
            int w = g->edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (int j = 0; j < E; j++) {
        int u = g->edges[j].src;
        int v = g->edges[j].dest;
        int w = g->edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Grafo possui ciclo negativo\n");
            free(dist);
            return;
        }
    }

    for (int i = 0; i < V; i++)
        printf("Distância do vértice %d até %d: %d\n", src, i, dist[i]);

    free(dist);
}

int main() {
    int V = 5;
    int E = 8;
    Graph* g = createGraph(V, E);

    g->edges[0].src = 0; g->edges[0].dest = 1; g->edges[0].weight = -1;
    g->edges[1].src = 0; g->edges[1].dest = 2; g->edges[1].weight = 4;
    g->edges[2].src = 1; g->edges[2].dest = 2; g->edges[2].weight = 3;
    g->edges[3].src = 1; g->edges[3].dest = 3; g->edges[3].weight = 2;
    g->edges[4].src = 1; g->edges[4].dest = 4; g->edges[4].weight = 2;
    g->edges[5].src = 3; g->edges[5].dest = 2; g->edges[5].weight = 5;
    g->edges[6].src = 3; g->edges[6].dest = 1; g->edges[6].weight = 1;
    g->edges[7].src = 4; g->edges[7].dest = 3; g->edges[7].weight = -3;

    bellmanFord(g, 0);

    free(g->edges);
    free(g);

    return 0;
}
