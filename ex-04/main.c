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

lista *troco(lista *c, int valor){
    lista *s = criar_lista();
    int soma = 0;

    while(c != NULL && soma < valor){
        int m = c->valor;
        if(soma + m <= valor){
            soma = soma + m;
            adicionar_no(s, c->valor);
        } else {
            c = c->prox;
        }
    }

    if (soma == valor){
        return s;
    } else {
        return NULL;
    }
}

int main(){
    lista *c = criar_lista();
    adicionar_no(c, 25);
    adicionar_no(c, 10);
    adicionar_no(c, 5);
    
    lista *valor_atual = troco(c, 47);
    if(valor_atual == NULL){
        printf("Não foi encontrada solução\n");
    } else {
       imprimir_lista(valor_atual);
    }

    deletar_lista(c);
    deletar_lista(valor_atual);

    return 0;
}