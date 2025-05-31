#include <stdlib.h>
#include <stdio.h>

#define SIZE 9

void mostra_matriz(int m[SIZE][SIZE]){
    printf("-----\n");
    for(int i = 0; i < SIZE; i++){
        if(i % 3 == 0)
                printf("-----------------------\n");
        for(int j = 0; j < SIZE; j++){
            if(j % 3 == 0)
                printf("| ");

            printf("%d ", m[i][j]);
        }    
        printf("\n");
    }
    printf("-----\n");
}

int valor_valido(int valor, int m[SIZE][SIZE],  int linha, int coluna){
    for(int i = 0; i < SIZE; i++){
        if(m[linha][i] == valor || m[i][coluna] == valor)
            return 0;
    }

    int bloco_linha = (linha / 3) * 3;
    int bloco_coluna = (coluna / 3) * 3;
    for (int i = bloco_linha; i < bloco_linha + 3; i++) {
        for (int j = bloco_coluna; j < bloco_coluna + 3; j++) {
            if (m[i][j] == valor)
                return 0;
        }
    }

    return 1;
}

void sudoku(int m[SIZE][SIZE], int linha, int coluna){
    if (coluna == SIZE){
        linha++;
        coluna = 0;
    }

    if(linha == SIZE){
        mostra_matriz(m);
    } else if(m[linha][coluna] > 0)
        sudoku(m, linha, coluna + 1);
    else {
        for(int i = 1; i <= SIZE; i++){
            if(valor_valido(i, m, linha, coluna)){
                m[linha][coluna] = i;
                sudoku(m, linha, coluna + 1);
                m[linha][coluna] = 0;
            }
        }
    }

}

int main(){

    int matriz[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    sudoku(matriz, 0, 0);

    return 0;
}