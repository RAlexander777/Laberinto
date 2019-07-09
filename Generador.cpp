#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <windows.h>

#define Dim 160  // 80 * 2= 160 ; 80 representa el ancho de la pantalla de consola
#define Celdas 6400  // 80 * 80 = 6400
#define muro 1 // La pared es true
#define camino 0 // El camino es false

using namespace std;

void gotoxy(int x,int y);
void Finesi();
void Menu();
void Puntos();

void plantilla(int laberinto[Dim][Dim]);
void generador(int indeks, int laberinto[Dim][Dim], int x_retorno[Celdas], int y_retorno[Celdas], int x, int y, int n, int visitado);
void mostrar(int laberinto[Dim][Dim], int dimension);
int sin_salida(int laberinto[Dim][Dim], int x, int y);

void gotoxy(int x,int y)
{  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos); 
}

void Puntos()
{
	for(int i=0; i<3; i++)
	{
		cout<<".";
		Sleep(1000);
	}
}

void Finesi()
{
	gotoxy(37,11);
	cout<<"F"; Sleep(100);
	cout<<"I"; Sleep(100);
	cout<<"N"; Sleep(100);
	cout<<"E"; Sleep(100);
	cout<<"S"; Sleep(100);
	cout<<"I"; Sleep(1000);
	
	gotoxy(2,21);
	cout<<"Creado Por:";
	gotoxy(2,22);
	cout<<"Rodrigo Alexander Becerra Lucano";
	Sleep(4000);
	system("cls");
}

void plantilla(int laberinto[Dim][Dim])
{
     for(int i= 0; i< Dim; i++)
     {
         for(int j= 0; j< Dim; j++)
         {
             if(i%2==0 || j%2==0)
                 laberinto[i][j]= 1;
             else
                 laberinto[i][j]= camino;
         }
     }
     
}

void generador(int indeks, int laberinto[Dim][Dim], int x_retorno[Celdas], int y_retorno[Celdas], int x, int y, int n, int visitado)
{
    if(visitado< n*n)
    {
        int vecino_true= -1;
        int vecino_x[4];
        int vecino_y[4];
        int pasos[4];

        int x_sig;
        int y_sig;

        if(x - 2 > 0 && sin_salida(laberinto, x - 2, y))  // Arriba
        {
            vecino_true++;
            
            vecino_x[vecino_true]=x-2;;
            vecino_y[vecino_true]=y;
            
            pasos[vecino_true]=1;
        }

        if(y - 2 > 0 && sin_salida(laberinto, x, y - 2))  // Izquierda
        {
            vecino_true++;
            
            vecino_x[vecino_true]= x;
            vecino_y[vecino_true]= y-2;
            
            pasos[vecino_true]=2;
        }

        if(y + 2< n * 2 + 1 && sin_salida(laberinto, x, y + 2))  // Derecha
        {
            vecino_true++;
            vecino_x[vecino_true]=x;
            vecino_y[vecino_true]=y + 2;
            pasos[vecino_true]=3;

        }

        if(x + 2< n * 2 + 1 && sin_salida(laberinto, x + 2, y))  // Abajo
        {
            vecino_true++;
            vecino_x[vecino_true]=x+2;
            vecino_y[vecino_true]=y;
            pasos[vecino_true]=4;
        }

        if(vecino_true == -1)
        {
            x_sig = x_retorno[indeks];
            y_sig = y_retorno[indeks];
            indeks--;
        }

        if(vecino_true!=-1)
        {
            int asignar = vecino_true + 1;
            int random = rand()%asignar;
            x_sig = vecino_x[random];
            y_sig = vecino_y[random];
            indeks++;
            x_retorno[indeks]= x_sig;
            y_retorno[indeks]= y_sig;

            int rpasos = pasos[random];

            if(rpasos == 1)
                laberinto[x_sig+1][y_sig]= camino;
            else if(rpasos == 2)
                laberinto[x_sig][y_sig + 1]= camino;
            else if(rpasos == 3)
                laberinto[x_sig][y_sig - 1]= camino;
            else if(rpasos == 4)
                laberinto[x_sig - 1][y_sig]= camino;
            visitado++;
        }

        generador(indeks, laberinto, x_retorno, y_retorno, x_sig, y_sig, n, visitado);
    }
}

void mostrar(int laberinto[Dim][Dim], int dimension)
{
	ofstream lab;
	
	lab.open("Laberinto.txt", ios::trunc);
	lab.close();

    for(int i= 0; i< dimension * 2 + 1; i++)
    {
     	
     	lab.open("Laberinto.txt", ios::app);
     	
        for(int j= 0; j< dimension * 2 + 1; j++)
        {
            if(laberinto[i][j]== muro)
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

int sin_salida(int laberinto[Dim][Dim], int x, int y)
{
    if(laberinto[x-1][y]==muro && laberinto[x][y-1]==muro && laberinto[x][y+1]==muro && laberinto[x+1][y]==muro)
        return 1;

    return 0;
}

void Menu()
{
	
	int dimension;
	char op;
	
	gotoxy(22,9);
	cout<<"Ingresa la dimension del laberinto: ";
	
	gotoxy(39,11);
	cin>>dimension;
	
	system("cls");
	
	if(dimension > 78)
	{
		gotoxy(20,11);
		cout<<"La dimension maxima permitida es 78*78";
		Sleep(3000);
		system("cls");
		return Menu();
	}

    srand(time(NULL));
    int tamanio= dimension / 2;
    int indeks= 0;
    int laberinto[Dim][Dim];
    int x_retorno[Celdas];
    int y_retorno[Celdas];

    plantilla(laberinto);

    x_retorno[indeks]= 1;
    y_retorno[indeks]= 1;
    
    gotoxy(35,11);
    cout<<"Generando";
    Puntos();
    
    system("cls");

    generador(indeks, laberinto, x_retorno, y_retorno, 1, 1, tamanio, 1);
    laberinto[0][1]= laberinto[tamanio * 2][tamanio * 2 - 1]= ' ';
    mostrar(laberinto, tamanio);

	if(dimension <= 40)
	{
	    gotoxy(dimension+5,3);
	    cout<<"Generar otro Laberinto? (Y/N)";
	    gotoxy(dimension+18,5);
	    cin>>op;
	}
	
	else if(dimension > 40)
	{
		gotoxy(1,dimension+5);
	    cout<<"Generar otro Laberinto? (Y/N): ";
	    gotoxy(35,dimension+5);
	    cin>>op;
	}
    
    if(op=='Y')
    {
    	system("cls");
		Menu();
	}
	
	else
	{
		system("cls");
	}
}

int main()
{
	system("color 0A");
	
	Finesi();
	
	Menu();
 
    return 0;
}
