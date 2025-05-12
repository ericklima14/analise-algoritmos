#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define INF INT_MAX - 1 //esse -1 é pra nao dar memory leak

int memoria[64];

void init_memoria() {
    memset(memoria, -1, sizeof(memoria));
}

int min(int a, int b){
    return a > b ? b : a;
}

int conta_moedas_recursivo(int T, int n, int *M){
    if (T == 0)
        return 0;

    if(T < 0)
        return INF;

    int menor = INF;
    for(int i = 0; i < n; i++){
        menor = min(menor, conta_moedas_recursivo(T - M[i], n, M) + 1);
    }
    return menor;
}

int conta_moedas_top_down(int T, int n, int *M){
    if(T == 0)
        return 0;
    if (T < 0)
        return INF;
    if(memoria[T] != -1)
        return memoria[T];
    
    int menor = INF;

    for(int i = 0; i < n; i++){
        menor = min(menor, conta_moedas_top_down(T - M[i], n, M) + 1);
    }
    memoria[T] = menor;
    return memoria[T];
}

int conta_moedas_bottom_up(int T, int n, int *M){
    int troco[T + 1];

    for(int i = 1; i <= T; i++){
        troco[i] = INF;
    }

    troco[0] = 0;

    for(int i = 1; i <= T; i++){
        for(int j = 0; j < n; j++){
            if(i >= M[j]){
                troco[i] = min(troco[i], troco[i - M[j]] + 1);
            }
        }
    }

    return troco[T];
}

int main(){
    int T = 11;
    int n = 3;
    int M[] = {1, 2, 5};

    int res_rec = conta_moedas_recursivo(T, n, M);
    if (res_rec >= INF) 
        printf("Recursivo: sem solucao para T=%d\n", T);
    else               
        printf("Recursivo: %d moedas para T=%d\n", res_rec, T);

    init_memoria();
    int res_td = conta_moedas_top_down(T, n, M);
    if (res_td >= INF) 
        printf("Top-Down: sem solucao para T=%d\n", T);
    else               
        printf("Top-Down: %d moedas para T=%d\n", res_td, T);

    int res_bu = conta_moedas_bottom_up(T, n, M);
    if (res_bu >= INF) 
        printf("Bottom-Up: sem solucao para T=%d\n", T);
    else               
        printf("Bottom-Up: %d moedas para T=%d\n", res_bu, T);

    return 0;
}