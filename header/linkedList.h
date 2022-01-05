#ifndef linkedList_h
#define linkedList_h

#define TAMPOP 10
#define MAX_INFO_LEN 10

typedef struct individuo{
    int info[MAX_INFO_LEN];
    struct individuo *prox;
} cromossomo;

void imprimir_lista (cromossomo * lista);
void initPopulation (cromossomo * lista);

cromossomo * criar_no (int data[MAX_INFO_LEN]);
cromossomo *criar_lista (int initial_data[]);
cromossomo *adicionar_lista (cromossomo *head, int data[]);

#endif