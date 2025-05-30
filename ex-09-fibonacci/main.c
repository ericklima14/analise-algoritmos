#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int memoria[64];

void init_memoria() {
    memset(memoria, -1, sizeof(memoria));
}

int fib_recursivo(int n){
    if(n == 0 || n == 1)
        return n;
    
    return fib_recursivo(n - 1) + fib_recursivo(n - 2);
}

int fib_dinamico_recursivo(int n){
    if(memoria[n] != -1)
        return memoria[n];
    else if(n == 0 || n == 1)
        memoria[n] = n;
    else
        memoria[n] = fib_dinamico_recursivo(n - 1) + fib_dinamico_recursivo(n - 2);

    return memoria[n];
}

int fib_dinamico_iterativo(int n){
    int memo[64]= {-1};
    memo[0] = 0;
    memo[1] = 1;

    for(int i = 2; i <= n; i++){
        memo[i] = memo[i - 1] + memo[i - 2];
    }

    return memo[n];
}


int main(){
    int valor = 7;
    init_memoria();

    printf("Valor do fib_recursivo para o valor %d: %d\n", valor, fib_recursivo(valor));
    printf("Valor do fib_dinamico_recursivo para o valor %d: %d\n", valor, fib_dinamico_recursivo(valor));
    printf("Valor do fib_dinamico_iterativo para o valor %d: %d\n", valor, fib_dinamico_iterativo(valor));  
    
    return 0;
}