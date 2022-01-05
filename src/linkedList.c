#include <stdio.h>
#include <stdlib.h>
#include "../header/linkedList.h"

//Função para imprimir a matriz de dados da população
void printList (chromosome *list) {
    chromosome *tmp = list;
    int i=0;
    while (tmp != NULL) {
        printf ("Indivíduo %d: ", i);
            for (int i = 0; i < TAMPOP; i++)
                printf("%d ", tmp->info[i]);
            printf("\n");
        tmp = tmp->next;
        i++;
    }
}

//Função para criar nó da lista ligada
chromosome * createNode (int data[MAX_INFO_LEN]) {
    chromosome *result = malloc(sizeof(chromosome));
    for(int i = 0; i < MAX_INFO_LEN; i++)
        result->info[i] = data[i];
    result->next = NULL;
    return result;
}

//Função para inciar a lista ligada
chromosome *createList(int initial_data[]){
    chromosome *head;
    chromosome *init_data = createNode(initial_data);

    head = init_data;
    head->next = NULL;

    return head;
}

//Função para adicionar indivíduos na lista
chromosome *appendList(chromosome *head, int data[]){
    chromosome *tmp = head;
    chromosome *createdNode = createNode(data);

    while(tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = createdNode;
    return head;
}

//Função para iniciar uma população
void initPopulation(chromosome * list){
    int aux, vectorAux[MAX_INFO_LEN];

    for (int i=1; i<TAMPOP; i++) {
        for (int j=0; j < MAX_INFO_LEN; j++)
            vectorAux[j] = rand() %4;
        appendList(list, vectorAux);
    }
}