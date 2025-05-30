#include <stdio.h>

#define MAX 100
int memo[MAX][MAX][MAX];

void zera_matriz(int m[MAX][MAX], int l, int c) {
    for (int i = 0; i < l; i++)
        for (int j = 0; j < c; j++)
            m[i][j] = 0;
}

int multiplicar_recursivo(int A[MAX][MAX], int B[MAX][MAX], int i, int j, int k, int colA) {
    if (k >= colA) return 0;
    return A[i][k] * B[k][j] + multiplicar_recursivo(A, B, i, j, k + 1, colA);
}

void matriz_recursiva(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int linA, int colA, int colB) {
    for (int i = 0; i < linA; i++)
        for (int j = 0; j < colB; j++)
            C[i][j] = multiplicar_recursivo(A, B, i, j, 0, colA);
}

int multiplicar_topdown(int A[MAX][MAX], int B[MAX][MAX], int i, int j, int k, int colA) {
    if (k >= colA) return 0;
    if (memo[i][j][k] != -1) return memo[i][j][k];

    memo[i][j][k] = A[i][k] * B[k][j] + multiplicar_topdown(A, B, i, j, k + 1, colA);
    return memo[i][j][k];
}

void matriz_topdown(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int linA, int colA, int colB) {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            for (int k = 0; k < MAX; k++)
                memo[i][j][k] = -1;

    for (int i = 0; i < linA; i++)
        for (int j = 0; j < colB; j++)
            C[i][j] = multiplicar_topdown(A, B, i, j, 0, colA);
}

void matriz_bottomup(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int linA, int colA, int colB) {
    for (int i = 0; i < linA; i++) {
        for (int j = 0; j < colB; j++) {
            C[i][j] = 0;
            for (int k = 0; k < colA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void imprimir(int m[MAX][MAX], int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

int main() {
    int A[MAX][MAX] = {
        {1, 2},
        {3, 4}
    };

    int B[MAX][MAX] = {
        {5, 6},
        {7, 8}
    };

    int C[MAX][MAX];
    int linA = 2, colA = 2, colB = 2;

    printf("Resultado (recursivo):\n");
    zera_matriz(C, linA, colB);
    matriz_recursiva(A, B, C, linA, colA, colB);
    imprimir(C, linA, colB);

    printf("\nResultado (top-down):\n");
    zera_matriz(C, linA, colB);
    matriz_topdown(A, B, C, linA, colA, colB);
    imprimir(C, linA, colB);

    printf("\nResultado (bottom-up):\n");
    zera_matriz(C, linA, colB);
    matriz_bottomup(A, B, C, linA, colA, colB);
    imprimir(C, linA, colB);

    return 0;
}