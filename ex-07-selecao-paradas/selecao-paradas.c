#include <stdlib.h>
#include <stdio.h>

typedef struct LISTA{
    int valor;
    struct LISTA *prox;
} lista;

lista* criar_lista(){
    lista *l = (lista*)malloc(sizeof(lista));
    l->valor = 0;
    l->prox = NULL;

    return l;
}

void adicionar_no(lista *l, int valor){
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
        printf("Indice: %d - Valor: %d\n", index, l_aux->valor);
 
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

//selecao de paradas
lista* selecao_paradas(int *p, int size, int delta){
    lista *u = criar_lista();
    int ultima_pos = 0;

    for(int i = 1; i < size; i++){
        if(p[i] - ultima_pos > delta){
            ultima_pos = p[i - 1];
            adicionar_no(u, p[i - 1]);
        }
    }

    return u;
}

int main(){
    int p[7] = {1, 2, 3, 4, 5, 6, 7};
    lista *l = selecao_paradas(p, 7, 2);
    imprimir_lista(l); 
    deletar_lista(l);

    return 0;
}