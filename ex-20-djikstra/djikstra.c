#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

int minDistance(int dist[], int visited[], int V) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

void dijkstra(int** graph, int V, int src) {
    int* dist = (int*)malloc(V * sizeof(int));
    int* visited = (int*)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (int count = 0; count < V -1; count++) {
        int u = minDistance(dist, visited, V);
        if(u == -1) break;
        visited[u] = 1;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    for (int i = 0; i < V; i++)
        printf("Distância do vértice %d até %d: %d\n", src, i, dist[i]);

    free(dist);
    free(visited);
}

int main() {
    int V = 5;
    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)calloc(V, sizeof(int));
    }

    graph[0][1] = 10;
    graph[0][4] = 5;
    graph[1][2] = 1;
    graph[1][4] = 2;
    graph[2][3] = 4;
    graph[3][0] = 7;
    graph[3][2] = 6;
    graph[4][1] = 3;
    graph[4][2] = 9;
    graph[4][3] = 2;

    dijkstra(graph, V, 0);

    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}