#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h> 

// Inclusão da TAD
#include "../header/linkedList.h"
#include "../header/maze.h"

// Definições iniciais de variáveis globais 
#define TAMPOP 3000 // Tamanho da população 
#define N 33 // Número de blocos do labirinto 
#define MUT_TAX 2 // Taxa de mutação --> NO MÁXIMO 5% 
#define DIV 2 // Relação utilizada para fazer o crossover 
#define MAX_INFO_LEN 300 // Máximo de informações por indivíduos
#define GEN_MAX 500
int gen = 0; // Seta a primeira geração 

// Função que trabalha com a avaliação do fitness dos indivíduos
void FitnessFunction(float fitness[TAMPOP], int crom[MAX_INFO_LEN], unsigned char Ds[TAMPOP], int indiv){

    // Declaração de variáveis 
    unsigned char B = 0, R = 0, D = Ds[indiv];
    int ant = 10, atual = 10;

    // Enquanto a variável i for menor que a informação presente no cromossomo
    for(int i = 0; i < MAX_INFO_LEN; i++){
        // O atual assume o gene[i] do cromossomo 
        atual = crom[i];
        // Contagem das repetições
        if((ant == 0 && atual == 1) || (ant == 1 && atual == 0) || (ant == 2 && atual == 3) || (ant == 3 && atual == 2))
            R++;     
        // O anterior assume o gene[i] do cromossomo 
        ant = crom[i];

        // Caso haja a indicação que o indivíduo bateu, o mesmo tira um bloco que ele andou 
        if(crom[i] == 5){
            B = i - 1;
            break;
        }
    }

    fitness[indiv] = (90/(D + 1)) - (0.05)*R + (0.15)*B;
    printf("\nindiv %d: D = %d, R = %d, B = %d, fitness = %.2f", indiv, D, R, B, fitness[indiv]);
}

// Função de ordenação, fazendo com que os melhores fitness fiquem nos primeiros indíces do vetor
void bubbleSort(float arr[], int n){ 

    int i, j;
    float aux; 

    for(i = n; i >= 0; i--){
        for(j = n-i-2; j >= 0; j--){ 
            if(arr[j+1] > arr[j]){
                aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
        }
    }
}

// Função de busca, relacionando os indivíduos que tem os melhores fitness com os seus índices 
void search(float arr[TAMPOP], int n, float fitness, int maxIteration[], int index){

    int i, j, flag;
    
    for(i = 0; i < n; i++){
        flag = 0;
        if(arr[i] == fitness){
            for(j = 0; j < n/DIV; j++){
                if(maxIteration[j] == i){
                    flag = 1;
                }
            }
            if(flag == 0) 
                maxIteration[index] = i;
        }
    }
}

// Método de seleção elitista, tendo como intuito nunca perder 
// os 10% melhores indivíduos de todos
void Selection(float fitness[TAMPOP], int maxIteration[TAMPOP/DIV]){

    float vectorAux[TAMPOP];

    // Seta todas as iterações dos melhores indivíduos, inicialmente, como menos -1 
    for(int i = 0; i < TAMPOP/DIV; i++)
        maxIteration[i] = -1;

    // Passa o vetor que possui os fitness para um auxiliar
    for(int i = 0; i < TAMPOP; i++)
        vectorAux[i] = fitness[i];

    // Faz uma ordenação no vetor de fitness 
    bubbleSort(vectorAux, TAMPOP);

    // Faz uma busca de acordo com índice e o fitness, relacionando-os 
    for(int i = 0; i < TAMPOP/DIV; i++) 
        search(fitness, TAMPOP, vectorAux[i], maxIteration, i);

}

// Manipula os dados da moda
void ModaData(int crom[MAX_INFO_LEN], int modaData[MAX_INFO_LEN][4]){

    for(int i = 0; i < MAX_INFO_LEN; i++){
        // Se o cromossmo tiver algum gene que seja maior que 3, ou seja, que tenha batido ou vá bater
        // ele para de contabilizar a moda 
        if(crom[i] > 3) 
            break;
        modaData[i][crom[i]]++;
    }
}

// Faz a moda dos cromossmos 
void Moda(int modaData[MAX_INFO_LEN][4], int moda[MAX_INFO_LEN]){

    // Passa por todo vetor moda setando o mesmo com valores aleatórios entre 0 e 4
    for(int i = 0; i < MAX_INFO_LEN; i++) 
        moda[i] = 0;

    for(int i = 0; i < MAX_INFO_LEN; i++){
        for(int j = 0; j < 4; j++){
            // Se os dados presente na matriz modaData[i][j] forem maiores
            // que os presentes na matriz modaData[i][moda[i]]
            if(modaData[i][j] > modaData[i][moda[i]])
                // O vetor moda com índice i assume o valor de j
                moda[i] = j;
        }
    }
}

void Predation(int maxIteration[TAMPOP/DIV], float fitness[TAMPOP], int crom[MAX_INFO_LEN], int bestcrom[MAX_INFO_LEN], int indiv){

    if(fitness[indiv] < (fitness[maxIteration[0]])/2)
        for(int j = 0; j < MAX_INFO_LEN; j++)
            crom[j] = bestcrom[j];
}

// Após proteger os melhores indivíduos, é necessário incluir
// os genes dos mesmos ao restante da população
void Crossover(int crom[], int moda[MAX_INFO_LEN], int step, int best){

    // Declaração de variáveis 
    float x;
    // obs: step = gen, nessa função gen é usado como o passo para aplicação do crossover
    
    // para cada step (geração) da função ele aplicará um peso diferente
    if(step < 10)
        step *= 9;
    else if(step > 10 && step < 25)
        step *= 7;
    else if(step > 25 && step < 50)
        step *= 5;
    else if(step > 50 && step < 100)
        step *= 3;
    else if(step > 100 && step < 150)
        step *= 2;

    // crossover rodando todo o cromossomo
    for (int i = 0; i < MAX_INFO_LEN; i++){
        // crossover para os não melhores de todos
        if(best == 0){
            // até o passo ele provavelmente deve pegar a moda dos melhores
            if(i < step){
                x = rand() % 101;
                if(x < 95)
                    crom[i] = moda[i];
                else
                    crom[i] = rand() % 4;
            }
            // do passo para frente tudo randomizado
            else{
                crom[i] = rand() % 4;
            }
        }
        // crossover para os melhores de todos
        else if(best == 1){
            // randomiza só a partir que ele bater
            if (crom[i] > 3)
                crom[i] = rand() % 4;
        }
    }
}

// Função que organiza os arquivos
void manageFitnessFile(float fitness[TAMPOP], int gen, int header){

    // relative file path
    char path[1000] = { };
    strcat(path, ""); // in case we want to use a different relative path
    strcat(path, "data_fitness.txt");

    // open the file
    FILE *file;
    
    chdir("src"); // change working directory to file manipulation
    file = fopen(path, "r" ); // file open
    // check any erros opening the file
    if (!file){
        printf("\nFailed to open text file\n");
        exit(1);
    }
    fclose(file);
    
    // header
    if(header == 1){
        file = fopen(path, "w");
        fprintf(file, "%s", "Arquivo de dados do FITNESS do Micromouse Evolutivo\n");
        fprintf(file, "%s", "TAMPOP = ");
        fprintf(file, "%d", TAMPOP);
        fprintf(file, "%s", "\tMAX_INFO_LEN = ");
        fprintf(file, "%d", MAX_INFO_LEN);
        fprintf(file, "%s", "\n");
        fclose(file);
    }
    // append fitness of all generations
    else{
        file = fopen(path, "a");    

        fprintf(file, "%s", "\nGeneration: ");
        fprintf(file, "%d", gen);
        fprintf(file, "%s", "\n\n");

        for(int i=0; i < TAMPOP; i++){
            fprintf(file, "%.2f", fitness[i]);    
            fprintf(file, "%s", " ");
        }
        fprintf(file, "%s", "\n");
        fclose(file);
    }
    chdir(".."); // change back to the original directory
}

void manageJSFile(int bestcrom[MAX_INFO_LEN], float fitmedia, float fitmax, int gen, int header){

    // relative file path
    char path[1000] = { };
    strcat(path, ""); // in case we want to use a different relative path
    strcat(path, "data_JS.txt");

    // Open the file
    FILE *file;
    
    chdir("src"); // change working directory to file manipulation
    file = fopen(path, "r" );
    // check any erros opening the file
    if (!file){
        printf("\nFailed to open text file\n");
        exit(1);
    }
    fclose(file);
    
    // header = 1: Cabecalho, header = 0: adicionar indv, header 2: preparar prox geracao
    if(header == 1){
        file = fopen(path, "w");
        fprintf(file, "%s", "Arquivo de dados dos CROMOSSOMOS do Micromouse Evolutivo\n");
        fprintf(file, "%d", TAMPOP);
        fprintf(file, "%s", "\n");
        fprintf(file, "%d", MAX_INFO_LEN);
        fprintf(file, "%s", "\n\n");
        fclose(file);
    }
    else if(header == 0){
        file = fopen(path, "a");    

        for(int i=0; i < MAX_INFO_LEN; i++){
            fprintf(file, "%d", bestcrom[i]);    
            fprintf(file, "%s", " ");
        }
        fprintf(file, "%s", "\n");
        fprintf(file, "%.2f", fitmedia);
        fprintf(file, "%s", "\n");
        fprintf(file, "%.2f", fitmax);
        fprintf(file, "%s", "\n\n");
        fclose(file);
    }
    chdir(".."); // change back to the original directory
}

void setMain(chromosome *temp, int crom[MAX_INFO_LEN], int gen, int i, unsigned char Maze[N][N], unsigned char Ds[TAMPOP], int input, float fitness[TAMPOP], int maxIteration[TAMPOP/DIV], int modaData[MAX_INFO_LEN][4], int moda[MAX_INFO_LEN]){

    int bestcrom[MAX_INFO_LEN];
    float fitmedia = 0; 
    switch(input){
    // move in maze
    case 0:
        while(temp != NULL){
            for(int j = 0; j < MAX_INFO_LEN; j++)
                crom[j] = temp->info[j];
            moveInMaze(Maze, crom, 1, 1, Ds, i);
            for(int j = 0; j < MAX_INFO_LEN; j++)
                temp->info[j] = crom[j];
            temp = temp->next;
            i++;
        }
        break;
    // fitness function
    case 1:
        while(temp != NULL){
            for(int j = 0; j < TAMPOP; j++)
                crom[j] = temp->info[j];
            FitnessFunction(fitness, crom, Ds, i);
            temp = temp->next;
            i++;
        }
        break;
    // moda
    case 2:
        while(temp != NULL){
            for(int j = 0; j < TAMPOP/DIV; j++){
                if(i == maxIteration[j]){
                    for (int k = 0; k < MAX_INFO_LEN; k++) 
                        crom[k] = temp->info[k];
                    ModaData(crom, modaData);
                }
            }
            temp = temp->next;
            i++;
        }
        break;
    // predation
    case 3:
        while(temp != NULL){
            // acha o melhor de todos e copia para o bestcrom
            if(i == maxIteration[0])
                for(int k = 0; k < MAX_INFO_LEN; k++)
                    bestcrom[k] = temp->info[k];
            // aplica a predação
            for(int j = 0; j < TAMPOP; j++){
                for(int k = 0; k < MAX_INFO_LEN; k++)
                    crom[k] = temp->info[k];
                Predation(maxIteration, fitness, crom, bestcrom, i);  
                for(int k = 0; k < MAX_INFO_LEN; k++) 
                    temp->info[k] = crom[k];
                // aproveitar o loop para calcular a media do fitness
                fitmedia += fitness[j];
            }
            fitmedia = fitmedia/TAMPOP;
            temp = temp->next;
            i++;
        }
        break;
    // crossover
    case 4:
        while(temp != NULL){
            int flagCrossover = 0;
            for (int j = 0; j < TAMPOP/DIV; j++) 
                if(i == maxIteration[j])
                    flagCrossover = 1;

            if(flagCrossover == 0){
                for(int k = 0; k < MAX_INFO_LEN; k++)
                    crom[k] = temp->info[k];
                Crossover(crom, moda, gen, 0); 
                for(int k = 0; k < MAX_INFO_LEN; k++)
                    temp->info[k] = crom[k];
            } else {
                for(int k = 0; k < MAX_INFO_LEN; k++) 
                    crom[k] = temp->info[k];
                Crossover(crom, moda, gen, 1);
                for(int k = 0; k < MAX_INFO_LEN; k++) 
                    temp->info[k] = crom[k];
            }
            temp = temp->next;
            i++;
        }
        break;
    case 5:
        while(temp != NULL){
            // acha o melhor de todos e copia para o bestcrom
            if(i == maxIteration[0])
                for(int k = 0; k < MAX_INFO_LEN; k++)
                    bestcrom[k] = temp->info[k];

            for(int j = 0; j < TAMPOP; j++)
                fitmedia += fitness[j];
            fitmedia = fitmedia/TAMPOP;
            temp = temp->next;
            i++;
        }
        // aproveita o loop para passar os cromossomos
        manageJSFile(bestcrom, fitmedia, fitness[maxIteration[0]], gen, 0); 
        break;
    }
}

int main(){
    
    // Determina uma seed diferente a cada run do código
    srand(time(NULL));

    // Declaração de varíaveis 

    chromosome *list;
    unsigned char Maze[N][N];
    int vector[MAX_INFO_LEN];
    float* fitness = (float *)calloc(TAMPOP, sizeof(float));
    unsigned char Ds[TAMPOP];
    
    manageFitnessFile(fitness, 0, 1);
    manageJSFile(fitness, 0, 0, 0, 1);

    // Randomiza todos os elementos do vetor que contém as informações 
    // genética dos indivíduos 
    for (int i = 0; i < MAX_INFO_LEN; i++)
        vector[i] = rand() % 4;

    // Criação da lista para armazenamento dos indivíduos
    list = createList(vector);
    // Iniciação da população 
    initPopulation(list);
    // Criação do labirinto 
    MazeCreation(Maze);

    // Repetição que forma as gerações 

    for(int aux = 0; aux < GEN_MAX; aux++){

        printf("Generation %d\n", gen);

        int i = 0;
        int vectorAux[MAX_INFO_LEN];
    
        //* MAZE
        chromosome *temp0 = list;
        setMain(temp0, vectorAux, gen, i, Maze, Ds, 0, 0, 0, 0, 0);
        i = 0;

        //* FITNESS FUNCTION
        printf("\nFITNESS");
        chromosome *temp1 = list;
        setMain(temp1, vectorAux, gen, i, Maze, Ds, 1, fitness, 0, 0, 0);
        printf("\n");
        i = 0;

        manageFitnessFile(fitness, gen, 0);

        //* SELECTION
        int maxIteration[TAMPOP/DIV];
        Selection(fitness, maxIteration); 

        //* MODA
        int modaData[MAX_INFO_LEN][4] = {};
        chromosome *temp3 = list;
        setMain(temp3, vectorAux, gen, i, Maze, Ds, 2, fitness, maxIteration, modaData, 0);
        i = 0;

        int *moda;
        moda = (int *)calloc(MAX_INFO_LEN, sizeof(int));

        Moda(modaData, moda);

        //* PREDATION
        chromosome *temp2 = list;
        if(gen == 100 || gen == 180){        
            printf("\nPREDAÇÃO");
            setMain(temp2, vectorAux, gen, i, Maze, Ds, 3, fitness, maxIteration, 0, 0);
        }
        i = 0;

        setMain(temp3, vectorAux, gen, i, Maze, Ds, 5, fitness, maxIteration, modaData, moda);

        //* Crossover e Mutação
        chromosome *temp4 = list;

        if(gen != 100 || gen != 180)            
            setMain(temp4, vectorAux, gen, i, Maze, Ds, 4, fitness, maxIteration, modaData, moda);

        i = 0;
        printf("\n");
        gen++;        
    }

    return 0;
}