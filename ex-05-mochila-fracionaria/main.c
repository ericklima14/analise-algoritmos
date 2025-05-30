#include <stdlib.h>
#include <stdio.h>

typedef struct LISTA{
    float valor;
    struct LISTA *prox;
} lista;

lista* criar_lista(){
    lista *l = (lista*)malloc(sizeof(lista));
    l->valor = 0;
    l->prox = NULL;

    return l;
}

void adicionar_no(lista *l, float valor){
    if(l->valor == 0){
        l->valor = valor;
        l->prox = NULL;

        return;
    }

    if(l->prox != NULL)
        adicionar_no(l->prox, valor);
    else {
        lista *novo_no = (lista*)malloc(sizeof(lista));

        if(!novo_no){
            printf("Não foi possivel alocar a memoria para um novo nó");
            return;
        }

        novo_no->valor = valor;
        novo_no->prox = NULL;
        l->prox = novo_no;

        return;
    }
}

void imprimir_lista(lista *l){
    lista *l_aux = l;
    int index = 0;

    while(l_aux != NULL){
        printf("Indice: %d - Valor: %.2f\n", index, l_aux->valor);
 
        l_aux = l_aux->prox;
        index++;
    }

    return;
}

void deletar_lista(lista *l){
    while(l != NULL){
        lista *l_aux = l;
        l = l->prox;

        free(l_aux);
    }

    return;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *w, int *v, int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(w[j]/v[j] <  w[j + 1]/v[j + 1]){
                swap(&w[j], &w[j + 1]);
                swap(&v[j], &v[j + 1]);
            }
        }
    }
}

lista *mochila_fracionaria(int *w, int *v, int n, int W){
    lista *x = criar_lista();
    bubble_sort(w, v, n);
    int i = 0;

    while(i <= n && W > 0){
        if(w[i] <= W){
            adicionar_no(x, w[i]);
            W -= w[i];
            i++;
        } else {
            adicionar_no(x, W/w[i]);
            W = 0;
        }
    }

    return x;
}

int main(){
    int w[3] = {10, 20, 30};
    int v[3] = {60, 100, 120};
    int W = 50;

    lista *s = mochila_fracionaria(w, v, 3, W);
    imprimir_lista(s);

    deletar_lista(s);
    return 0;
}