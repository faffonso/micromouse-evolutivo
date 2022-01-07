#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../header/linkedList.h"

// Definição inicial do tamanho da população e do tamanho do labirinto 
#define TAMPOP 10
#define N 33
#define MUT_TAX 

// Número de informações máxima (movimentos para chegar na solução) presentes em um cromossomo 
#define MAX_INFO_LEN 10

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
    if(flag == 1)
        for(int m = gene + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 5;

    if(flag == 2)
        for(int m = gene + 1; m < MAX_INFO_LEN; m++)
            crom[m] = 6;
}


void FitnessFunction(float fitness[TAMPOP], int crom[MAX_INFO_LEN], unsigned char Ds[TAMPOP], int indiv){

    // meio é em N-1/2 no x e no y

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


    fitness[indiv] = (100/(D + 1)) - (0.3)*R - (0.1)*B;
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

int search(float arr[], int n, float fitness, int maxIteration[]){
    int i, j;
    for (i = 0; i < n; i++)
        if (arr[i] == fitness)
            for (j = 0; j < n; j++) {
                if (maxIteration[j] == -1)
                    return j;
            }
}

void Selection(float fitness[TAMPOP], int maxIteration[TAMPOP/2]){

    float vectorAux[TAMPOP];
    int aux;
    for (int i=0; i < TAMPOP/2; i++) {
        maxIteration[i] = -1;
    }

    for (int i = 0; i < TAMPOP; i++)
        vectorAux[i] = fitness[i];

    bubbleSort(vectorAux, TAMPOP);

    for (int i = 0; i < TAMPOP/2; i++) {
        aux = search(fitness, TAMPOP, vectorAux[i], maxIteration);
        maxIteration[i] = aux;
    }
}

// TODO: Crossover dos cromossomos, lembrando que os do melhor indíviduos são "misturados" com o dos outros
// GIAN
void Crossover(float fitness[TAMPOP], int crom[MAX_INFO_LEN], int modaData[MAX_INFO_LEN][4], ){
    for (int i = 0; i < MAX_INFO_LEN; i++) {
        modaData[i][crom[i]]++;
        printf("Adicionando cromossomo %d, para %d\n", modaData[i][crom[i]], crom[i]);
    }
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

    file = fopen("data.txt", "a");    

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

    //* DECLARAÇÕES
    chromosome *list;
    unsigned char Maze[N][N];
    int vector[MAX_INFO_LEN];
    float fitness[TAMPOP];
    unsigned char Ds[TAMPOP];
    FILE *file;
    
    file = fopen("data.txt", "w");
    fprintf(file, "%s", "Arquivo de dados do Micromouse Evolutivo\n");
    fprintf(file, "%s", "TAMPOP = ");
    fprintf(file, "%d", TAMPOP);
    fprintf(file, "%s", "\tMAX_INFO_LEN = ");
    fprintf(file, "%d", MAX_INFO_LEN);
    fprintf(file, "%s", "\n");
    fclose(file);

    for (int i = 0; i < MAX_INFO_LEN; i++)
        vector[i] = rand() % 4;

    list = createList(vector);
    initPopulation(list);
    printList(list);
    MazeCreation(Maze);

    //* MOVE IN MAZE
    
    int vectorAux[MAX_INFO_LEN];
    chromosome *tmp0 = list;
    int i=0;
    while (tmp0 != NULL) {
        
        for (int j = 0; j < MAX_INFO_LEN; j++)
            vectorAux[j] = tmp0->info[j];
        moveInMaze(Maze, vectorAux, 1, 1, Ds, i);
        for (int j = 0; j < MAX_INFO_LEN; j++)
            tmp0->info[j] = vectorAux[j];
        tmp0 = tmp0->next;
        i++;
    } i = 0;

    
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

    int maxIteration[TAMPOP/2];
    int modaData[MAX_INFO_LEN][4];
    for (int i = 0; i < MAX_INFO_LEN; i++)
        for (int j = 0; j < 4; j++)
            moddaData[i][j] = 0;
    Selection(fitness, maxIteration);
    chromosome *tmp2 = list;
    while (tmp2 != NULL) {
        
        for (int j = 0; j < TAMPOP; j++)
            vectorAux[j] = tmp2->info[j];

        for (int j = 0; j < TAMPOP; j++) {
            if (i == maxIteration[j])
                Crossover(fitness, vectorAux, modaData);
        }
        tmp2 = tmp2->next;
        i++;
    } i = 0;

    printf("\n");

    printList(list);
    manageFile(file, fitness, 0);

    printf("\n");
    fclose(file);
    free(tmp0);
    free(tmp1);
    free(tmp2);

    return 0;
}