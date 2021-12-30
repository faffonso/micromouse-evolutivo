#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definição inicial do tamanho da população e do tamanho do labirinto 
#define TAMPOP 10
#define N 7

// Número de informações máxima presentes em um cromossomo 
#define MAX_INFO_LEN 100

typedef struct individuo{
    int cromossomos[MAX_INFO_LEN];
    struct individuo *prox;
} cromossomos;

typedef struct individuo *listaIndividuos;

typedef struct{
    listaIndividuos *genes;
} lista;

float fit[TAMPOP]; // fitness para cad individuo
int generation = 0;

listaIndividuos *criar_genes{

    listaIndividuos *genes = (listaIndividuos *) calloc (TAMPOP, sizeof (listaIndividuos));

    return genes;
}

void inserir_genes(listaIndividuos *genes, int gene){

    int aux;

    cromossomos *novoCromossomos = (cromossomos *) calloc (MAX_INFO_LEN, sizeof (cromossomos));

    aux = novoCromossomos->cromossomos;
    novoCromossomos->prox = *genes;
    *genes = novoCromossomos;
}

lista *criar_lista(lista *tabela, int gene){

    tabela->genes = calloc (1, sizeof (lista));

    tabela->genes = criar_genes(gene);

    return tabela;
}

// TODO: Criar o labirinto (montar a matriz e o labirinto com as paredes 0 e os espaços livres 1)
// no começo podemos só usar um labiritno exemplo - TOMAS
int MazeCreation(int Maze){
    

}

// TODO: Fazer a movimentação dos indivíduos dentro do labirinto
// cada individuo vai ter um cromossomo com os movimentos deles, essa funçaõ deve fazer essa mov.
// ela que vai dizer em que bloco que ele parou até bater em uma parede ou até chegar no destino
// sugestão: se ele bateu na nº possição do cromossomo, da n-ésima + 1 pra frente deixar tudo 5
// sugestão: se ele chegou na soluçao na nº posição, da n-ésima pra frente deixar tudo 6 - TOMAS
int MoveinMaze(int Maze){

}

// TODO: Iniciar população 
// GIAN
int InitPopulation(){
    for (int i = 0; i < TAMPOP; i++){
        inserir_genes(&tabela->genes[rand() % 1000]);
    }
}

// TODO: Criar função de avaliação 
// TOMAS
int FitnessFunction(){
    
}

// TODO: Tipo de avaliação que será feita para escolher os melhores indíviduos, no nosso caso é interessante utilizar uma que seja mais elitista
// incluindo a predação - GIAN
int Selection(){

}

// TODO: Crossover dos cromossomos, lembrando que os do melhor indíviduos são "misturados" com o dos outros
// GIAN
int Crossover(){

}

// TODO: Mutação dos indíviduos a partir do crossover feito anteriormente
// GIAN
int Mutation(){

}

// TODO: Rearranja população mutada para o início de uma nova geração 
// GIAN 
int RearrangePop(){

}


int main(){

    //matriz de individuos com cada cromossomo 
    int **inds = (int **)calloc(TAMPOP, sizeof(int)); 
    int i = 0;
    while(i < TAMPOP){
        inds[i]= (int *)calloc(TAMPOP, sizeof(int));
        i++;}


    srand(time(NULL));
    
    int Maze[7][7] = {{0, 0, 0, 0, 0, 0 ,0},
                    {0, 1, 1, 1, 1, 1 ,0},
                    {0, 1, 0, 0, 0, 1 ,0},
                    {0, 1, 0, 2, 1, 1 ,0},
                    {0, 1, 0, 0, 0, 0 ,0},
                    {0, 1, 1, 1, 1, 1 ,0},
                    {0, 0, 0, 0, 0, 0 ,0}};
    // 0 = parede, 1 = caminho, 2 = objetivo
    // acho que essa ta funcionando

    for (int i = 0; i < 6; i++)
        printf("Maze: %d\n", Maze[0][i]);


    //MoveinMaze(Maze);

    
    return 0;
}