#include <stdio.h>
#include <stdlib.h>
#include "../header/linkedList.h"

//Função para imprimir a matriz de dados da população
void imprimir_lista (cromossomo *lista) {
    cromossomo *aux = lista;
    int i=0;
    while (aux != NULL) {
        printf ("Indivíduo %d: ", i);
            for (int i = 0; i < TAMPOP; i++) {
                printf("%d ", aux->info[i]);
            }
            printf("\n");
        aux = aux->prox;
        i++;
    }
}

//Função para criar nó da lista ligada
cromossomo * criar_no (int data[MAX_INFO_LEN]) {
    cromossomo *result = malloc(sizeof(cromossomo));
    for(int i = 0; i < MAX_INFO_LEN; i++) {
        result->info[i] = data[i];
    }
    result->prox = NULL;
    return result;
}

//Função para inciar a lista ligada
cromossomo *criar_lista(int initial_data[]){
    printf("\n");
    cromossomo *head;
    cromossomo *init_val = criar_no(initial_data);

    head = init_val;
    head->prox = NULL;

    return head;
}

//Função para adicionar indivíduos na lista
cromossomo *adicionar_lista(cromossomo *head, int data[]){
    cromossomo *tmp = head;
    cromossomo *createdNode = criar_no(data);

    while(tmp->prox != NULL){
        tmp = tmp->prox;
    } 

    tmp->prox = createdNode;
    return head;
}

//Função para inciar uma população
void initPopulation(cromossomo * lista){
    int aux, vectorAux[MAX_INFO_LEN];

    for (int i=1; i<TAMPOP; i++) {
        for (int j=0; j < MAX_INFO_LEN; j++) {
            vectorAux[j] = rand() %4;
        }
        adicionar_lista(lista, vectorAux);
    }
}