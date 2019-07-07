#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#define MAX 173  /// 86 * 2 + 1 = 173
#define CELL 7500  /// 86 * 86 = 7396
#define muro 1
#define camino 0

using namespace std;

void init_maze(int maze[MAX][MAX]);
void maze_generator(int indeks, int maze[MAX][MAX], int x_retorno[CELL], int y_retorno[CELL], int x, int y, int n, int visitado);
void print_maze(int maze[MAX][MAX], int dimension);
int is_closed(int maze[MAX][MAX], int x, int y);

void init_maze(int maze[MAX][MAX])
{
     for(int i= 0; i< MAX; i++)
     {
         for(int j= 0; j< MAX; j++)
         {
             if(i%2==0 || j%2==0)
                 maze[i][j]= 1;
             else
                 maze[i][j]= camino;
         }
     }
     
}

void maze_generator(int indeks, int maze[MAX][MAX], int x_retorno[CELL], int y_retorno[CELL], int x, int y, int n, int visitado)
{
    if(visitado< n*n)
    {
        int neighbour_valid= -1;
        int neighbour_x[4];
        int neighbour_y[4];
        int step[4];

        int x_sig;
        int y_sig;

        if(x - 2 > 0 && is_closed(maze, x - 2, y))  // upside
        {
            neighbour_valid++;
            
            neighbour_x[neighbour_valid]=x-2;;
            neighbour_y[neighbour_valid]=y;
            
            step[neighbour_valid]=1;
        }

        if(y - 2 > 0 && is_closed(maze, x, y - 2))  // leftside
        {
            neighbour_valid++;
            
            neighbour_x[neighbour_valid]= x;
            neighbour_y[neighbour_valid]= y-2;
            
            step[neighbour_valid]=2;
        }

        if(y + 2< n * 2 + 1 && is_closed(maze, x, y + 2))  // rightside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x;
            neighbour_y[neighbour_valid]=y + 2;
            step[neighbour_valid]=3;

        }

        if(x + 2< n * 2 + 1 && is_closed(maze, x + 2, y))  // downside
        {
            neighbour_valid++;
            neighbour_x[neighbour_valid]=x+2;
            neighbour_y[neighbour_valid]=y;
            step[neighbour_valid]=4;
        }

        if(neighbour_valid == -1)
        {
            // backtrack
            x_sig = x_retorno[indeks];
            y_sig = y_retorno[indeks];
            indeks--;
        }

        if(neighbour_valid!=-1)
        {
            int randomization = neighbour_valid + 1;
            int random = rand()%randomization;
            x_sig = neighbour_x[random];
            y_sig = neighbour_y[random];
            indeks++;
            x_retorno[indeks]= x_sig;
            y_retorno[indeks]= y_sig;

            int rstep = step[random];

            if(rstep == 1)
                maze[x_sig+1][y_sig]= camino;
            else if(rstep == 2)
                maze[x_sig][y_sig + 1]= camino;
            else if(rstep == 3)
                maze[x_sig][y_sig - 1]= camino;
            else if(rstep == 4)
                maze[x_sig - 1][y_sig]= camino;
            visitado++;
        }

        maze_generator(indeks, maze, x_retorno, y_retorno, x_sig, y_sig, n, visitado);
    }
}

void print_maze(int maze[MAX][MAX], int dimension)
{
	ofstream lab;
	
	lab.open("Laberinto.txt", ios::trunc);
	lab.close();

    for(int i= 0; i< dimension * 2 + 1; i++)
    {
     	
     	lab.open("Laberinto.txt", ios::app);
        for(int j= 0; j< dimension * 2 + 1; j++)
        {
            if(maze[i][j]== muro)
            {
            	cout<<"1";
                lab<<"1";
            }
            
            else
            {
            	cout<<" ";
                lab<<" ";
            }
            
        }
        cout<<"\n";
        lab<<"\n";
        lab.close();
    }
}

int is_closed(int maze[MAX][MAX], int x, int y)
{
    if(maze[x-1][y]==muro && maze[x][y-1]==muro && maze[x][y+1]==muro && maze[x+1][y]==muro)
        return 1;

    return 0;
}

int main()
{
	
	int dimension;
	
	system("color 0A");
	
	cout<<"\n Ingresa la dimension del laberinto: ";
	cin>>dimension;
	
	system("cls");

    srand(time(NULL));
    int size= dimension / 2;
    int indeks= 0;
    int maze[MAX][MAX];
    int x_retorno[CELL];
    int y_retorno[CELL];

    init_maze(maze);

    x_retorno[indeks]= 1;
    y_retorno[indeks]= 1;

    maze_generator(indeks, maze, x_retorno, y_retorno, 1, 1, size, 1);
    maze[0][1]= maze[size * 2][size * 2 - 1]= ' ';
    print_maze(maze, size);

    return 0;
}
