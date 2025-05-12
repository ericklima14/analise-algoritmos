#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROW 100
#define COL 1000

int memoria[ROW + 1][COL + 1];

void init_memoria() {
    memset(memoria, -1, sizeof(memoria));
}

int max(int a, int b){
    return a > b ? a : b;
}

int maior_valor_recursivo(int n, int W, int *w, int *v){
    if(n < 0 || W <= 0){
        return 0;
    } 
    if(w[n - 1] > W){
        return maior_valor_recursivo(n - 1, W, w, v);
    } else{
        return max(maior_valor_recursivo(n - 1, W, w, v),
         maior_valor_recursivo(n - 1, W - w[n - 1], w, v) + v[n - 1]);
    }
}

int maior_valor_top_down(int n, int W, int *w, int *v){
    if(n < 0 || W <= 0){
        return 0;
    }
    if(memoria[n][W] != -1){
        return memoria[n][W];
    }
    if(w[n - 1] > W){
        memoria[n][W] = maior_valor_top_down(n - 1, W, w, v);
    } else {
        memoria[n][W] = max(maior_valor_top_down(n - 1, W, w, v), maior_valor_top_down(n - 1, W - w[n - 1], w, v) + v[n - 1]);
    }

    return memoria[n][W];
}

int maior_valor_bottom_up(int n, int W, int *w, int *v){
    int M[n + 1][W + 1];

    for(int i = 0; i <= n; i++) M[i][0] = 0;
    for(int j = 0; j <= W; j++) M[0][j] = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= W; j++){
            if(w[i - 1] > j){
                M[i][j] = M[i - 1][j];
            } else {
                M[i][j] = max(M[i - 1][j], M[i - 1][j - w[i - 1]] + v[i - 1]);
            }
        }
    }

    return M[n][W];
}

int main(){
    int w[] = {2, 3, 4, 5};
    int v[] = {3, 4, 5, 6};
    int n = 4, W = 5;

    printf("Recursivo: %d\n", maior_valor_recursivo(n, W, w, v));

    init_memoria();
    printf("Top-Down: %d\n", maior_valor_top_down(n, W, w, v));

    printf("Bottom-Up: %d\n", maior_valor_bottom_up(n, W, w, v));

    return 0;
}