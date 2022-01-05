#include <stdio.h>
#include <stdlib.h>
#include "../header/linkedList.h"

//Função para imprimir a matriz de dados da população
void printList(chromosome *list){

    // Cria uma struct temporária para armazenar os elementos da lista principal
    chromosome *tmp = list;

    int i=0;

    // Enquanto não houverem elementos "NULL" a lista continuará printando cada elemento
    while(tmp != NULL){

        printf ("Indivíduo %d: ", i);
            for (int i = 0; i < TAMPOP; i++)
                printf("%d ", tmp->info[i]);
            printf("\n");

        tmp = tmp->next;
        i++;
    }
}

//Função para criar nó da lista ligada
chromosome *createNode(int data[MAX_INFO_LEN]){

    // Aloca dinamicamente uma struct do tipo chromosome para armazenar os nós 
    chromosome *result = malloc(sizeof(chromosome));

    // Percorre a lista e armazena as informações desejadas
    for(int i = 0; i < MAX_INFO_LEN; i++)
        result->info[i] = data[i];

    result->next = NULL;
    
    // Retorna o nós armazenados, inicialmente como "NULL"
    return result;
}

//Função para inciar a lista ligada
chromosome *createList(int initial_data[]){

    // Cria duas structs, uma para ser a principal e outra para armazenar os dados inicialmente
    chromosome *head;
    chromosome *init_data = createNode(initial_data);

    // A principal armazena os dados da struct inicial e os seta como "NULL"
    head = init_data;
    head->next = NULL;

    return head;
}

//Função para adicionar indivíduos na lista
chromosome *appendList(chromosome *head, int data[]){

    // Cria duas sturcts, uma para armazenar os dados principais temporariamenet
    // e outra para a criação dos nós dos elementos que serão adicionados
    chromosome *tmp = head;
    chromosome *createdNode = createNode(data);

    // Enquanto o próximo nó for diferente de "NULL",
    // continua a adicionar os elementos 
    while(tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = createdNode;

    return head;
}

//Função para iniciar uma população
void initPopulation(chromosome *list){

    int aux, vectorAux[MAX_INFO_LEN];

    // Armazena um número aleatório entre 0 e 4 no vetor auxiliar
    // para ser guardado na lista de cromossomos
    for (int i = 1; i < TAMPOP; i++) {
        for (int j=0; j < MAX_INFO_LEN; j++)
            vectorAux[j] = rand() %4;

        appendList(list, vectorAux);
    }
}