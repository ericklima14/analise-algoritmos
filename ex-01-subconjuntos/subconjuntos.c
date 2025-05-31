#include <stdlib.h>
#include <stdio.h>

void imprimirSubconjunto(int subconjunto[], int tamanho) {
    printf("{");
    for (int i = 0; i < tamanho; i++) {
        if (i > 0) printf(", ");
        printf("%d", subconjunto[i]);
    }
    printf("}\n");
}

void gerarSubconjuntos(int vetor[], int n, int indice, int subconjunto[], int tamanhoSubconjunto) {
    if (indice == n) {
        imprimirSubconjunto(subconjunto, tamanhoSubconjunto);
        return;
    }

    gerarSubconjuntos(vetor, n, indice + 1, subconjunto, tamanhoSubconjunto);

    subconjunto[tamanhoSubconjunto] = vetor[indice];
    gerarSubconjuntos(vetor, n, indice + 1, subconjunto, tamanhoSubconjunto + 1);
}

void todosSubconjuntos(int vetor[], int n) {
    int subconjunto[n];
    gerarSubconjuntos(vetor, n, 0, subconjunto, 0);
}

int main() {
    int vetor[] = {1, 5, 9};
    int n = sizeof(vetor) / sizeof(vetor[0]);
    todosSubconjuntos(vetor, n);
    return 0;
}