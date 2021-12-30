#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definição inicial do tamanho da população e do tamanho do labirinto 
#define TAMPOP 10
#define N 7

// Número de informações máxima (movimentos para chegar na solução) presentes em um cromossomo 
#define MAX_INFO_LEN 10

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

lista *criar_genes(){

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

    tabela->genes = calloc (1, sizeof (lista)); // QEU TABELA PORRA

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
int MoveinMaze(int Maze[7][7], int crom[MAX_INFO_LEN], int x, int y){

    int flag;
    // flag = 0 ANDANDO, flag = 1 BATEU, flag = 2 CHEGOU

    for(int m = 0; m < 7; m++){
        for(int n = 0; n < 7; n++)
            printf(" %d ", Maze[m][n]);
        printf("\n");   
    }    

    int i = 0;
    while(i < MAX_INFO_LEN){
        switch (crom[i]){       
            case 0: // left
                printf("\nmaze[%d][%d-1] = %d", y, x, Maze[y][x-1]);
                if(Maze[y][x - 1] == 0){
                    printf("\nBATEU");
                    flag = 1;
                    break;
                }
                else if(Maze[y][x - 1] == 2){
                    printf("\nCHEGOU NA SOLUCAO");
                    flag = 2;
                    break;
                }
                printf("\nANDANDO");
                x--; // left
                break;
            case 1: // right
                printf("\nmaze[%d,%d+1] = %d", y, x, Maze[y][x+1]);
                if(Maze[y][x + 1] == 0){
                    printf("\nBATEU");
                    flag = 1;
                    break;
                }
                else if(Maze[y][x + 1] == 2){
                    printf("\nCHEGOU NA SOLUCAO");
                    flag = 2;
                    break;
                }
                printf("\nANDANDO");
                x++; // right
                break;
            case 2: // up
                printf("\nmaze[%d - 1,%d] = %d", y, x, Maze[y-1][x]);
                if(Maze[y - 1][x] == 0){
                    printf("\nBATEU");
                    flag = 1;
                    break;
                }
                else if(Maze[y - 1][x] == 2){
                    printf("\nCHEGOU NA SOLUCAO");
                    flag = 2;
                    break;
                }
                printf("\nANDANDO");
                y--; // up
                break;
            case 3: // down
                printf("\nmaze[%d+1,%d] = %d", y, x, Maze[y+1][x]);
                if(Maze[y + 1][x] == 0){
                    printf("\nBATEU");
                    flag = 1;
                    break;
                }
                else if(Maze[y + 1][x] == 2){
                    printf("\nCHEGOU NA SOLUCAO");
                    flag = 2;
                    break;
                }
                printf("\nANDANDO");
                y++; // down
                break;
        }
    if(flag == 1 || flag == 2)
        break;
    i++;    

    }

    if(flag == 1)
        for(int m = i + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 5;

    if(flag == 2)
        for(int m = i + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 6;

    for(int m = 0; m < MAX_INFO_LEN; m++)
        printf("\ncrom[m] = %d", crom[m]);
}

// TODO: Iniciar população 
// GIAN
int InitPopulation(int tabela){
    for (int i = 0; i < TAMPOP; i++){
        //inserir_genes(&tabela->genes[rand() % 1000]); //! QUE TABELA PORRA  ????
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

    int cromossomo_teste[MAX_INFO_LEN];

    for(int i = 0; i < MAX_INFO_LEN; i++){
        cromossomo_teste[i] = rand() % 4; // numero aleatorio entre 0 e 3
        printf("cromossomo_teste[%d] = %d\n", i, cromossomo_teste[i]);
    }

    int x0 = 5;
    int y0 = 5;

    MoveinMaze(Maze, cromossomo_teste, x0, y0);

    return 0;
}