#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h> 

// Inclusão da TAD
#include "../header/linkedList.h"
#include "../header/maze.h"

// Definições iniciais de variáveis globais 
#define TAMPOP 10 // Tamanho da população 
#define N 33 // Número de blocos do labirinto 
#define MUT_TAX // Taxa de mutação --> NO MÁXIMO 5%  
#define DIV 2 // Relação utilizada para fazer o crossover 
#define MAX_INFO_LEN 300 // Máximo de informações por indivíduos

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

    /*
    for(int i = 0; i < MAX_INFO_LEN; i++)
        if(crom[i] == 5){
            B = i - 1;
            break;
        }
    */

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
void ModaData(int crom[MAX_INFO_LEN], int modaData[MAX_INFO_LEN][4]) {

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
        moda[i] = rand() % 4;

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

// Após proteger os melhores indivíduos, é necessário incluir
// os genes dos mesmos ao restante da população
void Crossover(int crom[], int moda[], int gen){

    // Declaração de variáveis 
    float x;

    // Passa por todas as gerações 
    for(int i = 0; i < gen; i++){
        x = rand() % 101;
        //printf("\ncrom[i] = %d, moda[i] = %d, x = %f", crom[i], moda[i], x);
        if (x < 95)
            crom[i] = moda[i];
        else
            crom[i] = rand() % 4;
    }
    for (int i = gen; i < MAX_INFO_LEN; i++) 
        crom[i] = rand() % 4;
}

// Rearranja a população
void RearrangePop(int crom[]){
    for (int i = 0; i < MAX_INFO_LEN; i++)
        if (crom[i] > 3)
            crom[i] = rand() % 4;
    
}

// Função que organiza os arquivos
void manageFitnessFile(float fitness[TAMPOP], int gen, int header){

    // Relative file path
    char path[1000] = { };
    strcat(path, ""); // In case we want to use a different relative path
    strcat(path, "data_fitness.txt");

    // Open the file
    FILE *file;
    
    chdir("src"); // Change working directory to file manipulation
    file = fopen(path, "r" );
    if (!file){
        printf("\nFailed to open text file\n");
        exit(1);
    }
    fclose(file);
    
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
    chdir("..");
}

void manageJSFile(int crom[MAX_INFO_LEN], int indiv, int gen, int header){

    // relative file path
    char path[1000] = { };
    strcat(path, ""); // in case we want to use a different relative path
    strcat(path, "data_JS.txt");

    // Open the file
    FILE *file;
    
    chdir("src"); // change working directory to file manipulation
    file = fopen(path, "r" );
    if (!file){
        printf("\nFailed to open text file\n");
        exit(1);
    }
    fclose(file);
    
    // header = 1: Cabecalho, header = 0: adicionar indv, header 2: preparar prox geracao
    if(header == 1){
        file = fopen(path, "w");
        fprintf(file, "%s", "Arquivo de dados dos CROMOSSOMOS do Micromouse Evolutivo\n");
        fprintf(file, "%s", "TAMPOP = ");
        fprintf(file, "%d", TAMPOP);
        fprintf(file, "%s", "\tMAX_INFO_LEN = ");
        fprintf(file, "%d", MAX_INFO_LEN);
        fprintf(file, "%s", "\n");

        fprintf(file, "%s", "\nGeneration: 0\n\n");
        fclose(file);
    }
    else if(header == 0){
        file = fopen(path, "a");    

        fprintf(file, "%s", "indiv ");
        fprintf(file, "%d", indiv);
        fprintf(file, "%s", ":    ");

        for(int i=0; i < MAX_INFO_LEN; i++){
            fprintf(file, "%d", crom[i]);    
            fprintf(file, "%s", " ");
        }
        fprintf(file, "%s", "\n");
        fclose(file);
    }
    else if(header == 2){
        file = fopen(path, "a"); 
        fprintf(file, "%s", "\nGeneration: ");
        fprintf(file, "%d", gen);
        fprintf(file, "%s", "\n\n");
        fclose(file);
    }
    chdir("..");
}

void setMain(chromosome *temp, int crom[MAX_INFO_LEN], int gen, int i, unsigned char Maze[N][N], unsigned char Ds[TAMPOP], int input, float fitness[TAMPOP], int maxIteration[TAMPOP/DIV], int modaData[MAX_INFO_LEN][4], int moda[]){

    switch(input){
    case 0:
        while(temp != NULL){
            for (int j = 0; j < MAX_INFO_LEN; j++)
                crom[j] = temp->info[j];
            moveInMaze(Maze, crom, 1, 1, Ds, i);
            manageJSFile(crom, i, gen, 0);
            for (int j = 0; j < MAX_INFO_LEN; j++)
                temp->info[j] = crom[j];
            temp = temp->next;
            i++;
        }
        break;
    case 1:
        while(temp != NULL){
            for(int j = 0; j < TAMPOP; j++)
                crom[j] = temp->info[j];
            FitnessFunction(fitness, crom, Ds, i);
            temp = temp->next;
            i++;
        }
        break;
    case 2:
        while(temp != NULL){
            for (int j = 0; j < TAMPOP/DIV; j++) {
                if (i == maxIteration[j]) {
                    for (int k = 0; k < MAX_INFO_LEN; k++) 
                        crom[k] = temp->info[k];
                    ModaData(crom, modaData);
                }
            }

            temp = temp->next;
            i++;
        }
        break;
    case 3:
        while(temp != NULL){
            int flagCrossover = 0;
            for (int j = 0; j < TAMPOP/DIV; j++) 
                if(i == maxIteration[j]) 
                    flagCrossover = 1; 
            if(flagCrossover == 0){
                Crossover(crom, moda, gen); 
                for (int k = 0; k < MAX_INFO_LEN; k++){
                    temp->info[k] = crom[k];
                }
            } else {
                for (int k = 0; k < MAX_INFO_LEN; k++) 
                    crom[k] = temp->info[k];
                RearrangePop(crom); 
                for (int k = 0; k < MAX_INFO_LEN; k++) 
                    temp->info[k] = crom[k];
            }
            temp = temp->next;
            i++;
        } 
    }
}

int main(){
    
    // Determina uma seed diferente a cada run do código
    srand(time(NULL));

    // Declaração de varíaveis 
    chromosome *list;
    unsigned char Maze[N][N];
    int vector[MAX_INFO_LEN];
    float fitness[TAMPOP];
    unsigned char Ds[TAMPOP];
    
    manageFitnessFile(fitness, 0, 1);
    manageJSFile(fitness, 0, 0, 1);

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
    for(int aux = 0; aux < 50; aux++){

        printf("Generation %d\n",gen);

        // printList(list);

        int i = 0;
        int vectorAux[MAX_INFO_LEN];
        
        //* MAZE 

        chromosome *temp0 = list;

        setMain(temp0, vectorAux, gen, i, Maze, Ds, 0, 0, 0, 0, 0);

        i = 0;

        printf("\nPRE MANAGEJSFILE");

        manageJSFile(vectorAux, 0, gen, 2);

        //* FITNESS FUNCTION
        
        chromosome *temp1 = list;

        setMain(temp1, vectorAux, gen, i, Maze, Ds, 1, fitness, 0, 0, 0);

        i = 0;

        //* SELECTION

        int maxIteration[TAMPOP/DIV];
        Selection(fitness, maxIteration);

        //printf("\nMELHORES DE TODOS\n");
        //for (int i = 0; i < TAMPOP/DIV; i++) printf("%d ", maxIteration[i]);
        //printf("\n");    

        //* MODA
        int modaData[MAX_INFO_LEN][4];
        for (int i = 0; i < MAX_INFO_LEN; i++)
            for (int j = 0; j < 4; j++)
                modaData[i][j] = 0;

        chromosome *temp2 = list;

        setMain(temp2, vectorAux, gen, i, Maze, Ds, 2, fitness, maxIteration, modaData, 0);

        i = 0;

        int moda[MAX_INFO_LEN];
        Moda(modaData, moda);

        /* printf("\nTABELA\n");
        for (int i = 0; i < MAX_INFO_LEN; i++) {
            for (int j = 0; j < 4; j++) {
                printf ("%d ", modaData[i][j]);
            }
            printf("\n");
        } */

        // printf("\nMODA\n");
        // for (int i = 0; i < MAX_INFO_LEN; i++) printf("%d ", moda[i]);
        // printf("\n");

        // printf("\nAntes do CROSSOVER");
        // printList(list);

        //* Crossover e Mutação
        chromosome *temp3 = list;

        setMain(temp3, vectorAux, gen, i, Maze, Ds, 3, fitness, maxIteration, modaData, moda);

        i = 0;
        
        manageFitnessFile(fitness, gen, 0);

        // printf("\nDEPOIS DO CROSSOVER");
        // printList(list);

        printf("\n");

        gen++;
    }

    return 0;
}