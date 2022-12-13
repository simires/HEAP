#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HEAP * HEAP_create(int n, COMP * compara) { //criar heap; recebe seu tamanho e o parametro de comparacao entre os elementos
    HEAP * novo = malloc(sizeof(HEAP)); //ponteiro para o conjunto heap
    novo -> N = n; //tamanho da heap
    novo -> P = 0; //numero de elementos da heap
    novo -> elems = malloc(sizeof(void * ) * n); //alocar espaco para os elementos da heap
    for (int r = 0; r < n; r++) {
        novo -> elems[r] = NULL; //retirar lixo de memoria da heap
    }
    novo -> comparador = compara; //definir a funcao comparador do vetor
    return novo; // retornar a heap criada
}

void HEAP_add(HEAP * heap, void * newelem) { //adicionar elementos; recebe a heap e o novo elemento
    if (heap -> P < heap -> N) { //heap nao esta cheia
        if (heap -> P == 0) { //heap esta vazia
            heap -> elems[0] = newelem; //inserir elem na primeira posicao
            heap -> P++; //aumentar tam da heap sempre que um elem for adicionado
        } else { //heap nao esta vazia
            int pos = heap -> P; //iterador
            int pai = (pos - 1) / 2; //indice do pai
            heap -> elems[pos] = newelem; //adiciona na ultima posicao do vetor
            while (heap -> comparador(heap -> elems[pos], heap -> elems[pai]) == 1) { 
                //enquanto o elemento na posicao eh menor que o pai dele 
                void * aux = heap -> elems[pai]; //aux guarda o valor do pai
                heap -> elems[pai] = heap -> elems[pos]; //pai recebe o antigo filho
                heap -> elems[pos] = aux; //o antigo filho recebe o antigo pai
                pos = pai; //filho antigo se torna pai
                pai = (pos - 1) / 2; //novo indice do pai eh calculado
                if (pai < 0) break;
            }
            heap->P++; //aumentar o tam da heap sempre que um elem for adicionado
        }
    }
}

void* HEAP_remove(HEAP* heap){ //remover; recebe a heap e remove o seu primeiro elemento
    void* aux = heap->elems[0]; //guarda elem a ser removido
    heap->elems[0] = heap->elems[heap->P - 1]; //a posicao desocupada recebe o ultimo elem
    heap->elems[heap->P - 1] = NULL; //liberar a ultima posicao
    heap->P--; //reduzir o tamanho da heap

    int pos = 0; //iterador
    int f1, f2; //filho 1 e filho 2
    int menor;
    while(2*pos+1 < heap->P){ //percorrer toda a heap
        f1 = 2*pos+1; //indice filho 1
        f2 = 2*pos+2; //indice filho 2
        if(heap->elems[f1] != NULL && heap->elems[f2] != NULL){ //se o pai tem dois filhos
            menor = heap->elems[f1] < heap->elems[f2] ? f1 : f2; //menor vai guardar o menor dos valores entre os filhos
            if(heap->elems[menor] < heap->elems[pos]){ //se o filho for menor que o pai troca os valores
                void* aux = heap->elems[menor]; //aux guarda o menor filho
                heap->elems[menor] = heap->elems[pos]; //o antigo filho menor recebe o pai
                heap->elems[pos] = aux; //o antigo pai recebe o menor filho
                pos = menor; //atualizar o indice do pai
            } else break;
        } else{ //se o pai nao tem dois filhos
            if(heap->elems[f1] != NULL){ //se o pai tem somente o f1
                if(heap->elems[f1] < heap->elems[pos]){ //se o filho for menor que o pai, troca os valores entre eles
                    void* aux = heap->elems[f1];
                    heap->elems[f1] = heap->elems[pos];
                    heap->elems[pos] = aux;
                    pos = f1;
                } else break;
            } else{ //se o pai tem soente o filho 2
                if(heap->elems[f2] < heap->elems[pos]){ //se o filho 2 for menor que o pai, troca os valores
                    void* aux = heap->elems[f2];
                    heap->elems[f2] = heap->elems[pos];
                    heap->elems[pos] = aux;
                    pos = f2;
                } else break;
            }
        }
    }

    return aux; //retornar o valor removido
}