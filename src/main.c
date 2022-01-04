#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Definição inicial do tamanho da população e do tamanho do labirinto 
#define TAMPOP 10
#define N 33

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

    // Cria um ponteiro para um novo cromossomo do tipo cromossomo
    cromossomos *novoCromossomos = (cromossomos *) calloc (MAX_INFO_LEN, sizeof (cromossomos));

    // Copia o valor inteiro que será inserido para o novo cromossomo 
    aux = novoCromossomos->cromossomos;
    novoCromossomos->prox = *genes;
    *genes = novoCromossomos;
}

// Função do tipo lista que aponta para criar lista, criando a tabela para guardar os vetores de cromossomos
lista *criar_lista(lista *tabela, int gene){

    // Aloca dinamicamente um espaço de *tantas* posições para o vetor de genes
    tabela->genes = calloc (1,sizeof (lista));

    // Tabela que atribui os cromossomos da lista de genes 
    tabela->genes = criar_genes(gene); 

    // Retorna a tabela para a criação e inserção dos genes nos cromossomos de cada indíviduo 
    return tabela;
}

// TODO: Iniciar população
// GIAN
void initPopulation(lista *tabela, unsigned info){
    for (int i = 0; i < MAX_INFO_LEN; i++){
        // Era para inserir os genes de cada indíviduo na tabela, mas por enquanto tá dando erro
        inserir_genes(&tabela->genes[i], (double) (rand() % 1000));
    }
}

// TODO: Criar o labirinto (montar a matriz e o labirinto com as paredes 0 e os espaços livres 1)
// no começo podemos só usar um labiritno exemplo - TOMAS
int MazeCreation(int Maze[N][N]){
    

}

// funcao auxiliar da moveInMaze
void MazePosition(int Maze[N][N], int *x, int *y, int dx, int dy, int *flag, int Ds[TAMPOP], int indiv){
    
    // levanta a flag se bateu ou chegou na solução, caso contrario incrementa o passo e continua
    if(Maze[*y + dy][*x + dx] == 0)
        *flag = 1;
    else if(Maze[*y + dy][*x + dx] == 2)
        *flag = 2;
    else{
        *x = *x + dx;
        *y = *y + dy;
    }

    // calcula a distancia do ponto que bateu até o meio
    // meio = (N - 1)/2 em x e em y
    Ds[indiv] = abs(*x - (N - 1)/2) + abs(*y - (N - 1)/2);
}

// TODO: Fazer a movimentação dos indivíduos dentro do labirinto
// cada individuo vai ter um cromossomo com os movimentos deles, essa funçaõ deve fazer essa mov.
// ela que vai dizer em que bloco que ele parou até bater em uma parede ou até chegar no destino
// sugestão: se ele bateu na nº possição do cromossomo, da n-ésima + 1 pra frente deixar tudo 5
// sugestão: se ele chegou na soluçao na nº posição, da n-ésima pra frente deixar tudo 6 - TOMAS
void moveInMaze(int Maze[N][N], int crom[MAX_INFO_LEN], int x, int y, int Ds[TAMPOP], int indiv){

    // flag = 0 ANDANDO, flag = 1 BATEU, flag = 2 CHEGOU
    int flag;
    // Distancia para o cálculo do Fitness, dist = dx + dy (catetos até o meio)

    int gene = 0;
    while(gene < MAX_INFO_LEN){
        flag = 0;
        switch (crom[gene]){       
            case 0: // left
                MazePosition(Maze, &x, &y, -1, 0, &flag, Ds, indiv);
                break;
            case 1: // right
                MazePosition(Maze, &x, &y, +1, 0, &flag, Ds, indiv);
                break;
            case 2: // up
                MazePosition(Maze, &x, &y, 0, -1, &flag, Ds, indiv);
                break;
            case 3: // down
                MazePosition(Maze, &x, &y, 0, +1, &flag, Ds, indiv);
                break;
        }
        if(flag == 1 || flag == 2) 
            break;
        gene++;    
    }
    if(flag == 1)
        for(int m = gene + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 5;

    if(flag == 2)
        for(int m = gene + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 6;
}


// TODO: Criar função de avaliação 
// TOMAS
void FitnessFunction(float fitness[TAMPOP], int crom[MAX_INFO_LEN], int Ds[TAMPOP], int indiv){

    // meio é em N-1/2 no x e no y

    int B = 0, R = 0, D = Ds[indiv];


    int ant = 10, atual = 10;
    for(int i = 0; i < MAX_INFO_LEN; i++){
        atual = crom[i];
        if((ant == 0 && atual == 1) || (ant == 1 && atual == 0) || (ant == 2 && atual == 3) || (ant == 3 && atual == 2))
            R++;        
        ant = crom[i];
    }

    for(int i = 0; i < MAX_INFO_LEN; i++)
        if(crom[i] == 5){
            B = i - 1;
            break;
        }


    fitness[indiv] = (100/(D + 1)) - (0.3)*R - (0.1)*B;
    printf("\nindiv %d: D = %d, R = %d, B = %d, fitness = %.2f", indiv, D, R, B, fitness[indiv]);
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

void manageFile(FILE *file, float fitness[TAMPOP], int gen){

    file = fopen("dados.txt", "a");    

    fprintf(file, "%s", "\nGeneration: ");
    fprintf(file, "%d", gen);
    fprintf(file, "%s", "\n\n");


    for(int i=0; i < TAMPOP; i++){
        fprintf(file, "%.2f", fitness[i]);    
        fprintf(file, "%s", " ");
    }
}


int main(){

    srand(time(NULL));
    
    int Maze[N][N] =  { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                        {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
                        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 2, 2, 2, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    
    // 0 = parede, 1 = caminho, 2 = objetivo
    // acho que essa ta funcionando

    // Cria uma tabela do tipo lista
    lista tabela;

    // Cria uma lista com os cromossomos de cada indíviduo
    criar_lista(&tabela, MAX_INFO_LEN);

    printf("\nTabela:\n");
    for(int i = 0; i < TAMPOP; i++){
        for(int j = 0; j < MAX_INFO_LEN; j++){
            tabela.genes[j] = rand() % 4;
            printf(" %d ", tabela.genes[j]);
        }
        printf("\n");
    }

   //* TOMAS::

    int cromossomos[TAMPOP][MAX_INFO_LEN];
    float fitness[TAMPOP];
    int vet_aux[MAX_INFO_LEN];
    int Ds[TAMPOP];

    FILE *file;
    file = fopen("dados.txt", "w");
    fprintf(file, "%s", "Arquivo de dados do Micromouse Evolutivo\n");
    fclose(file);


    printf("\n\n");
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

    int x0 = 1;
    int y0 = 1;

    // gambiarra, mas no geral passa o a matriz de cromossomos individuo por individuo para o moveInMaze
    //* MOVE IN MAZE
    for(int i = 0; i < TAMPOP; i++){
        // copia o vetor pra um aux
        for(int j = 0; j < MAX_INFO_LEN; j++)
            vet_aux[j] = cromossomos[i][j];
        // chama a funcao moveInMaze
        moveInMaze(Maze, vet_aux, x0, y0, Ds, i);
        // copia de volta pro cromossomos
        for(int j = 0; j < MAX_INFO_LEN; j++)
            cromossomos[i][j] = vet_aux[j];
    }

    //* FITNESS FUNCTION
    for(int i = 0; i < TAMPOP; i++){
        for(int j = 0; j < MAX_INFO_LEN; j++)
            vet_aux[j] = cromossomos[i][j];
        FitnessFunction(fitness, vet_aux, Ds, i);
    }

    // printa a matriz de individuos atualizada
    printf("\n\n");
    for(int i = 0; i < TAMPOP; i++){
        for(int j = 0; j < MAX_INFO_LEN; j++){
            printf(" %d ", cromossomos[i][j]);
        }
        printf("\n");
    }

    manageFile(file, fitness, 0);

    printf("\n");

    fclose(file);
    return 0;
}