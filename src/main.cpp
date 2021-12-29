#include <iostream>
#include <string>
#include <exception>

#define TAMPOP 10
#define N 7; // tamanho do labirinto


//!ERRADO ISSO unsigned char crom[TAMPOP*TAMPOP]; // cromossomo 
float fit[TAMPOP]; // fitness para cad individuo
int generation = 0;

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

    //for (int i = 0; i < (TAMPOP*TAMPOP); i++){
    //    crom[i] = (double) (rand() % 1000); // define cada cromossomo do invíduo como um número aleatório 
    //}
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

    for (int i = 0; i < 6; i++){
        std::cout << "Maze: %d\n", Maze[0][i];
    }

    //MoveinMaze(Maze);
    
    std::cout << "hello world\n";
    return 0;
}