#ifndef linkedList_h
#define linkedList_h

#define TAMPOP 10
#define MAX_INFO_LEN 10

typedef struct individuo{
    int info[MAX_INFO_LEN];
    struct individuo *next;
} chromosome;

void printList (chromosome * list);
void initPopulation (chromosome * list);

chromosome * createNode (int data[MAX_INFO_LEN]);
chromosome *createList (int initial_data[]);
chromosome *appendList (chromosome *head, int data[]);

#endif