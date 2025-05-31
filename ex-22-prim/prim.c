#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

int minKey(int key[], int mstSet[], int V) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    return min_index;
}

void primMST(int** graph, int V) {
    int* parent = (int*)malloc(V * sizeof(int));
    int* key = (int*)malloc(V * sizeof(int));
    int* mstSet = (int*)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++) key[i] = INF;
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Arestas da MST:\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d : %d\n", parent[i], i, graph[i][parent[i]]);

    free(parent);
    free(key);
    free(mstSet);
}

int main() {
    int V = 5;
    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)calloc(V, sizeof(int));
    }

    graph[0][1] = 2; graph[1][0] = 2;
    graph[0][3] = 6; graph[3][0] = 6;
    graph[1][2] = 3; graph[2][1] = 3;
    graph[1][3] = 8; graph[3][1] = 8;
    graph[1][4] = 5; graph[4][1] = 5;
    graph[2][4] = 7; graph[4][2] = 7;
    graph[3][4] = 9; graph[4][3] = 9;

    primMST(graph, V);

    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}