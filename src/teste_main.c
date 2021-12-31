#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definição inicial do tamanho da população e do tamanho do labirinto 
#define TAMPOP 5
#define N 7

// Número de informações máxima (movimentos para chegar na solução) presentes em um cromossomo 
#define MAX_INFO_LEN 10

// Struct indivíduo do tipo cromossomos, contendo informações dos indivíduos 
typedef struct individuo{
    int cromossomos[MAX_INFO_LEN];
    struct individuo *prox;
} cromossomos;

// Struct indivíduo do tipo lista de indivíduos, formando uma TABELA PORRA
typedef struct individuo *listaIndividuos;

// Struct do tipo lista com vetor de inteiros, sendo eles os genes 
typedef struct{
    // Vetor do tipo lista de indivíduos com a quantidade de genes
    // necessários para completar o labirinto
    listaIndividuos *genes;
} lista;

float fit[TAMPOP]; // fitness para cad individuo
int generation = 0;

// Cria os genes da lista encadeada (lista de vetores >> matriz), sendo uma função do tipo lista 
lista *criar_genes(){

    // Aloca dinamicamente o espaço de TAMPOP posições do tamanho de inteiroes para a lista de genes 
    listaIndividuos *genes = (listaIndividuos *) calloc (TAMPOP, sizeof (listaIndividuos));

    // Retorna os genes da lista 
    return genes;
}

// Insere cada gene na lista, formando a lista encadeada
void inserir_genes(listaIndividuos *genes, int gene){

    int aux;

    // Cria um ponteiro para um novo cromossomo do tipo croomossomo
    cromossomos *novoCromossomos = (cromossomos *) calloc (MAX_INFO_LEN, sizeof (cromossomos));

    // Copia o valor inteiro que será inserido para o novo cromossomo 
    aux = novoCromossomos->cromossomos;
    novoCromossomos->prox = *genes;
    *genes = novoCromossomos;
}

// Função do tipo lista que aponta para criar lista, criando a tabela para guardar os vetores de cromossomos
lista *criar_lista(lista *tabela, int gene){

    // Aloca dinamicamente um espaço de *tantas* posições para o vetor de genes
    tabela->genes = calloc (1, sizeof (lista)); // QEU TABELA PORRA

    // Tabela que atribui os cromossomos da lista de genes 
    tabela->genes = criar_genes(gene); 

    // Retorna a tabela para a criação e inserção dos genes nos cromossomos de cada indíviduo 
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
int MoveinMaze(int Maze[N][N], int crom[MAX_INFO_LEN], int x, int y){

    int flag;
    // flag = 0 ANDANDO, flag = 1 BATEU, flag = 2 CHEGOU


    int i = 0;
    while(i < MAX_INFO_LEN){
        flag = 0;
        switch (crom[i]){       
            case 0: // left
                if(Maze[y][x - 1] == 0){
                    flag = 1;
                    break;
                }
                else if(Maze[y][x - 1] == 2){
                    flag = 2;
                    break;
                }
                x--; // left
                break;
            case 1: // right
                if(Maze[y][x + 1] == 0){
                    flag = 1;
                    break;
                }
                else if(Maze[y][x + 1] == 2){
                    flag = 2;
                    break;
                }
                x++; // right
                break;
            case 2: // up
                if(Maze[y - 1][x] == 0){
                    flag = 1;
                    break;
                }
                else if(Maze[y - 1][x] == 2){
                    flag = 2;
                    break;
                }
                y--; // up
                break;
            case 3: // down
                if(Maze[y + 1][x] == 0){
                    flag = 1;
                    break;
                }
                else if(Maze[y + 1][x] == 2){
                    flag = 2;
                    break;
                }
                y++; // down
                break;
        }
        if(flag == 1 || flag == 2){
            printf("\nBateu! movimento = %d", crom[i]);
            break;
        }
        i++;    
    }

    if(flag == 1)
        for(int m = i + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 5;

    if(flag == 2)
        for(int m = i + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 6;

    printf("\n>>> ");
    for(int m = 0; m < MAX_INFO_LEN; m++)
        printf(" %d ", crom[m]);
    printf("\n");
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
int FitnessFunction(int fitness, int crom[MAX_INFO_LEN]){

    // meio é em N+1/2 no x e no y
    //! Falta calcular a distancia, vou ter que mexer no código do MoveInMaze e fazer alguma baianagem

    int D = N/2; // só pra dar uma brincada
    int B = 0, R = 0;

    int ant = 0, atual = 0;
    for(int i = 0; i < MAX_INFO_LEN; i++){
        atual = crom[i];
        if(crom[i] == 5)
            B = i - 1;
        if((ant == 0 && atual == 1) || (ant == 1 && atual == 0) || (ant == 2 && atual == 3) || (ant == 3 && atual == 2))
            R++;
        ant = crom[i];
    }

    fitness = (100/(D + 1)) - (5)*R - (1)*B;

    return fitness;
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

    srand(time(NULL));
    
    int Maze[N][N] = {{0, 0, 0, 0, 0, 0 ,0},
                    {0, 1, 1, 1, 1, 1 ,0},
                    {0, 1, 0, 0, 0, 1 ,0},
                    {0, 1, 0, 2, 1, 1 ,0},
                    {0, 1, 0, 0, 0, 0 ,0},
                    {0, 1, 1, 1, 1, 1 ,0},
                    {0, 0, 0, 0, 0, 0 ,0}};
    // 0 = parede, 1 = caminho, 2 = objetivo
    // acho que essa ta funcionando

    int cromossomos[TAMPOP][MAX_INFO_LEN];
    int vet_aux[MAX_INFO_LEN];
    int fitness[TAMPOP];

    for(int i = 0; i < TAMPOP; i++){
        for(int j = 0; j < MAX_INFO_LEN; j++){
            cromossomos[i][j] = rand() % 4; // numero aleatorio entre 0 e 3
            printf(" %d ", cromossomos[i][j]);
        }
        printf("\n");
    }

    /* cromossomos:
    ind1 : 0, 1, 3, 2 ...
    ind2 : 1, 3, 0, 0 ...
    ...
    */

    int x0 = 5;
    int y0 = 5;

    // gambiarra, mas no geral passa o a matriz de cromossomos individuo por individuo para o MoveInMaze
    for(int i = 0; i < TAMPOP; i++){
        for(int j = 0; j < MAX_INFO_LEN; j++)
            vet_aux[j] = cromossomos[i][j];
        MoveinMaze(Maze, vet_aux, x0, y0);
        for(int j = 0; j < MAX_INFO_LEN; j++)
            cromossomos[i][j] = vet_aux[j];
    }

    for(int i = 0; i < TAMPOP; i++){
        for(int j = 0; j < MAX_INFO_LEN; j++)
            vet_aux[j] = cromossomos[i][j];
        FitnessFunction(fitness[i], vet_aux);
    }

    // printa a matriz de individuos atualizada
    for(int i = 0; i < TAMPOP; i++){
        for(int j = 0; j < MAX_INFO_LEN; j++){
            printf(" %d ", cromossomos[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < TAMPOP; i++)
        printf("\nfitness[%d] = %d", i, fitness[i]);

    return 0;
}