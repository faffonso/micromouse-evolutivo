#ifndef linkedList_h
#define linkedList_h

#define TAMPOP 10
#define MAX_INFO_LEN 100

// Stuct individual do tipo chromosome, contendo informações do indivíduo 
typedef struct individual{
    int info[MAX_INFO_LEN];
    struct individual *next;
} chromosome;

void printList(chromosome * list);
void initPopulation(chromosome * list);

chromosome *createNode(int data[MAX_INFO_LEN]);
chromosome *createList(int initial_data[]);
chromosome *appendList(chromosome *head, int data[]);

#endif