#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int memoria[64];

void init_memoria() {
    memset(memoria, -1, sizeof(memoria));
}

int max(int a, int b){
    return a > b ? a : b;
}

int LIS(int i, int *num){
    if(i == 0){
        return 1;
    }
    else {
        int maior = 1;
        for(int j = 0; j < i; j++){
            if(num[j] < num[i]){
                maior = max(maior, LIS(j, num) + 1);
            }
        }
        return maior;
    }
}

int LIS_memoization(int i, int *num){
    if(memoria[i] != -1){
        return memoria[i];
    } else if(i == 0){
        memoria[i] = 1;
        return memoria[i];
    } else {
        int maior = 1;
        for(int j = 0; j < i; j++){
            if(num[j] < num[i]){
                maior = max(maior, LIS_memoization(j, num) + 1);
            }
        }
        memoria[i] = maior;
        return memoria[i];
    }
}

int subsequencia_crescente_mais_longa(int *num, int n, int (func)(int i, int *num)){
    int maior = 1;
    for(int i = 0; i < n; i++){
        maior = max(maior, func(i, num));
    }

    return maior;
}

int subs_tabulation(int *num, int n){
    int L[n];

    for(int i = 0; i < n; i++){
        L[i] = 1;
    }

    int maior = 0;

    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(num[j] < num[i]){
                L[i] = max(L[i], L[j] + 1);
            }
            maior = max(maior, L[i]);
        }
    }

    return maior;
}

int main(){
    init_memoria();

    int num[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    int n = sizeof(num) / sizeof(num[0]);

    int lis_recursivo = subsequencia_crescente_mais_longa(num, n, LIS);
    printf("LIS (Recursivo Puro): %d\n", lis_recursivo);

    init_memoria();

    int lis_memoization = subsequencia_crescente_mais_longa(num, n, LIS_memoization);
    printf("LIS (Recursivo com Memoização): %d\n", lis_memoization);

    int lis_tabulation = subs_tabulation(num, n);
    printf("LIS (Iterativo com Tabulação): %d\n", lis_tabulation);
    return 0;
}