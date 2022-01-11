#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h> 

#include "../header/linkedList.h"

// Definição inicial do tamanho da população e do tamanho do labirinto 
#define TAMPOP 50
#define N 33
#define MUT_TAX 
#define DIV 2


// Número de informações máxima (movimentos para chegar na solução) presentes em um cromossomo 
#define MAX_INFO_LEN 300

int gen = 0;

void MazeCreation(unsigned char Maze[N][N]){
    
    // 0 = parede, 1 = caminho, 2 = objetivo
    int Maze1[N][N] =  {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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

    int Maze2[N][N] =  {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
                        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
                        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
                        {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0},
                        {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                        {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                        {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
                        {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                        {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
                        {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 2, 2, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
                        {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 2, 2, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
                        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 2, 2, 2, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
                        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                        {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
                        {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0},
                        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
                        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            Maze[i][j] = Maze1[i][j]; //* Trocar o Maze aqui

}

void MazePosition(unsigned char Maze[N][N], int *x, int *y, int dx, int dy, unsigned char *flag, unsigned char Ds[TAMPOP], int indiv){
    
    if((*x + dx) < 0 || (*y + dy) < 0)
        *flag = 1;

    // levanta a flag se bateu ou chegou na solução, caso contrario incrementa o passo e continua
    if((Maze[*y + dy][*x + dx] == 0))
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

void moveInMaze(unsigned char Maze[N][N], int crom[MAX_INFO_LEN], int x, int y, unsigned char Ds[TAMPOP], int indiv){

    // flag = 0 ANDANDO, flag = 1 BATEU, flag = 2 CHEGOU
    unsigned char flag;
    // Distancia para o cálculo do Fitness, dist = dx + dy (catetos até o meio)

    unsigned char gene = 0;
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
    if(flag == 1){
        crom[gene] = 4;
        for(int m = gene + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 5;
    }

    if(flag == 2)
        for(int m = gene + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 6;
    
}


void FitnessFunction(float fitness[TAMPOP], int crom[MAX_INFO_LEN], unsigned char Ds[TAMPOP], int indiv){

    unsigned char B = 0, R = 0, D = Ds[indiv];

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

    fitness[indiv] = (90/(D + 1)) - (0.05)*R + (0.1)*B;
    printf("\nindiv %d: D = %d, R = %d, B = %d, fitness = %.2f", indiv, D, R, B, fitness[indiv]);
}

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

void search(float arr[TAMPOP], int n, float fitness, int maxIteration[], int index){

    int i, j, flag;
    
    for(i = 0; i < n; i++) {
        flag = 0;
        if(arr[i] == fitness) {
            for(j = 0; j < n/DIV; j++) {
                if(maxIteration[j] == i) {
                    flag = 1;
                }
            }
            if (flag == 0) maxIteration[index] = i;
        }
    }
}

void Selection(float fitness[TAMPOP], int maxIteration[TAMPOP/10]){

    float vectorAux[TAMPOP];

    for(int i = 0; i < TAMPOP/DIV; i++)
        maxIteration[i] = -1;

    for(int i = 0; i < TAMPOP; i++)
        vectorAux[i] = fitness[i];

    bubbleSort(vectorAux, TAMPOP);

    for(int i = 0; i < TAMPOP/DIV; i++) search(fitness, TAMPOP, vectorAux[i], maxIteration, i);
    
}

void ModaData(int crom[MAX_INFO_LEN], int modaData[MAX_INFO_LEN][4]) {
    //Contabiliza as informações em uma matriz
    for (int i = 0; i < MAX_INFO_LEN; i++) {
        if (crom[i] > 3) break;
        modaData[i][crom[i]]++;
    }
}

void Moda (int modaData[MAX_INFO_LEN][4], int moda[MAX_INFO_LEN]) {
    //Seta o valor incial para a instrução 0 como moda
    for (int i = 0; i < MAX_INFO_LEN; i++) moda[i] = rand() % 4;

    //Verifica a maior moda, seta ela e seu valor correspondente para gráficos
    for (int i = 0; i < MAX_INFO_LEN; i++) {
        for (int j = 0; j < 4; j++) {
            //! Randomizar se tiver valorese iguais
            // sugestão: esclher a soma com mais fitness
            if(modaData[i][j] > modaData[i][moda[i]]) moda[i] = j;
        }
    }
}

// para os NAO melhores de todos
void Crossover(int crom[], int moda[], int gen){

    float x;

    for (int i = 0; i < gen; i++){
        x = rand() % 101;
        //printf("\ncrom[i] = %d, moda[i] = %d, x = %f", crom[i], moda[i], x);
        if (x < 85)
            crom[i] = moda[i];
        else
            crom[i] = rand() % 4;
    }
    for (int i = gen; i < MAX_INFO_LEN; i++) 
        crom[i] = rand() % 4;
}

// para os melhores de todos
void RearrangePop(int crom[]){
    for (int i = 0; i < MAX_INFO_LEN; i++)
        if (crom[i] > 3)
            crom[i] = rand() % 4;
    
}

void manageFitnessFile(float fitness[TAMPOP], int gen, int header){

    // relative file path
    
    char path[1000] = { };
    strcat(path, ""); // in case we want to use a different relative path
    strcat(path, "data_fitness.txt");

    // Open the file
    FILE *file;
    
    chdir("src"); // change working directory to file manipulation
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
        printf("\nNO JS FILE");
        fprintf(file, "%s", "\nGeneration: ");
        fprintf(file, "%d", gen);
        fprintf(file, "%s", "\n\n");
        fclose(file);
    }
    chdir("..");
}

int main(){
    
    srand(time(NULL));

    //* DECLARAÇÕES
    chromosome *list;
    unsigned char Maze[N][N];
    int vector[MAX_INFO_LEN];
    float fitness[TAMPOP];
    unsigned char Ds[TAMPOP];
    
    manageFitnessFile(fitness, 0, 1);
    manageJSFile(fitness, 0, 0, 1);

    for (int i = 0; i < MAX_INFO_LEN; i++)
        vector[i] = rand() % 4;

    list = createList(vector);
    initPopulation(list);
    MazeCreation(Maze);


    //* GERACOES
    for(int aux = 0; aux < 50; aux++){

        printf("Generation %d\n",gen);

        // printList(list);

        //* MOVE IN MAZE
        int vectorAux[MAX_INFO_LEN];
        chromosome *tmp0 = list;
        int i = 0;
        while (tmp0 != NULL) {
            
            for (int j = 0; j < MAX_INFO_LEN; j++)
                vectorAux[j] = tmp0->info[j];
            moveInMaze(Maze, vectorAux, 1, 1, Ds, i);
            manageJSFile(vectorAux, i, gen, 0);
            for (int j = 0; j < MAX_INFO_LEN; j++)
                tmp0->info[j] = vectorAux[j];
            tmp0 = tmp0->next;
            i++;
        } i = 0;
        printf("\nPRE MANAGEJSFILE");
        manageJSFile(vectorAux, 0, gen, 2);

        //* FITNESS FUNCTION
        
        chromosome *tmp1 = list;
        while (tmp1 != NULL) {
            
            for (int j = 0; j < TAMPOP; j++)
                vectorAux[j] = tmp1->info[j];

            FitnessFunction(fitness, vectorAux, Ds, i);
            tmp1 = tmp1->next;
            i++;
        } i = 0;

        //* SELECTION

        int maxIteration[TAMPOP/DIV];
        Selection(fitness, maxIteration);
        // printf("\nMELHORES DE TODOS\n");
        // for (int i = 0; i < TAMPOP/DIV; i++) printf("%d ", maxIteration[i]);
        // printf("\n");    

        //* MODA
        int modaData[MAX_INFO_LEN][4];
        for (int i = 0; i < MAX_INFO_LEN; i++)
            for (int j = 0; j < 4; j++)
                modaData[i][j] = 0;
        
        chromosome *tmp2 = list;
        while (tmp2 != NULL){
            for (int j = 0; j < TAMPOP/DIV; j++) {
                if (i == maxIteration[j]) {
                    for (int k = 0; k < MAX_INFO_LEN; k++) vectorAux[k] = tmp2->info[k];
                    ModaData(vectorAux, modaData);
                }
            }

            tmp2 = tmp2->next;
            i++;
        } i = 0;
        int moda[MAX_INFO_LEN];
        Moda (modaData, moda);

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
        chromosome *tmp3 = list;
        int flagCrossover;
        while (tmp3 != NULL){
            flagCrossover = 0;
            for (int j = 0; j < TAMPOP/DIV; j++) 
                if(i == maxIteration[j]) 
                    flagCrossover = 1; // ta nos melhores de todos
            if (flagCrossover == 0){
                Crossover(vectorAux, moda, gen); // crossover nos não melhores de todos
                for (int k = 0; k < MAX_INFO_LEN; k++){
                    tmp3->info[k] = vectorAux[k];
                }
            } else {
                for (int k = 0; k < MAX_INFO_LEN; k++) 
                    vectorAux[k] = tmp3->info[k];
                RearrangePop(vectorAux); // RearranjaPop nos melhores melhores de todos
                for (int k = 0; k < MAX_INFO_LEN; k++) 
                    tmp3->info[k] = vectorAux[k];
            }
            tmp3 = tmp3->next;
            i++;
        } i = 0;

        manageFitnessFile(fitness, gen, 0);

        // printf("\nDEPOIS DO CROSSOVER");
        // printList(list);

        printf("\n");
        free(tmp0);
        free(tmp1);
        free(tmp2);
        free(tmp3);

        gen++;
    }

    return 0;
}