#ifndef maze_h
#define maze_h

#define N 33 
#define TAMPOP 1000
#define MAX_INFO_LEN 300

void MazeCreation(unsigned char Maze[N][N]);
void MazePosition(unsigned char Maze[N][N], int *x, int *y, int dx, int dy, unsigned char *flag, unsigned char Ds[TAMPOP], int indiv);
void moveInMaze(unsigned char Maze[N][N], int crom[MAX_INFO_LEN], int x, int y, unsigned char Ds[TAMPOP], int indiv);

#endif
