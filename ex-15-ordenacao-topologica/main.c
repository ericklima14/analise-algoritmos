#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* --- Estruturas de dados para o grafo --- */

// Nó da lista de adjacência
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Grafo: vetor de ponteiros para lista de adjacência
typedef struct {
    int V;       // número de vértices
    Node** adj;  // adj[i] aponta para a lista de vizinhos de i
} Graph;

// Cria um novo nó de lista
Node* newNode(int dest) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->dest = dest;
    n->next = NULL;
    return n;
}

// Inicializa um grafo com V vértices
Graph* createGraph(int V) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->adj = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++)
        g->adj[i] = NULL;
    return g;
}

// Adiciona aresta u -> v
void addEdge(Graph* g, int u, int v) {
    Node* n = newNode(v);
    n->next = g->adj[u];
    g->adj[u] = n;
}

/* --- DFS recursiva + pilha para ordenação topológica --- */

// Visita recursiva a partir de v
void dfsVisit(Graph* g, int v, bool visited[], int stack[], int* top) {
    visited[v] = true;
    for (Node* p = g->adj[v]; p; p = p->next) {
        if (!visited[p->dest])
            dfsVisit(g, p->dest, visited, stack, top);
    }
    // ao terminar de visitar todos os adjacentes de v, empilha v
    stack[(*top)++] = v;
}

// Função principal de ordenação topológica
void topologicalSort(Graph* g) {
    bool* visited = (bool*)calloc(g->V, sizeof(bool));
    int* stack   = (int*)  malloc(g->V * sizeof(int));
    int  top     = 0;  // aponta para o próximo slot livre na pilha

    // inicia um DFS de cada vértice não visitado
    for (int i = 0; i < g->V; i++) {
        if (!visited[i])
            dfsVisit(g, i, visited, stack, &top);
    }

    // desempilha e imprime na ordem inversa ao término do DFS
    printf("Ordenação topológica:\n");
    for (int i = top - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");

    free(visited);
    free(stack);
}

/* --- Exemplo de uso --- */
int main() {
    int V = 6;
    Graph* g = createGraph(V);
    addEdge(g, 5, 2);
    addEdge(g, 5, 0);
    addEdge(g, 4, 0);
    addEdge(g, 4, 1);
    addEdge(g, 2, 3);
    addEdge(g, 3, 1);

    topologicalSort(g);

    // liberar grafo
    for (int i = 0; i < V; i++) {
        Node* p = g->adj[i];
        while (p) {
            Node* tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);

    return 0;
}