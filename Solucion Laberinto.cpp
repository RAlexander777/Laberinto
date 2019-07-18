#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string.h>
#include <time.h>

#define dim 160

using namespace std;

void gotoxy(int x,int y);


void gotoxy(int x,int y)
{  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos); 
}

int main()
{
    char Lab[dim][dim];
    int dimension;
    int b= 0;
    
    string txt;
    
    ifstream num;
	num.open("Dimension.txt", ios::in);
	
	getline(num, txt);
	
	gotoxy(2,22);
	cout<<txt;
	
	num.close();

    gotoxy(22,9);
	cout<<"Ingresa la dimension del laberinto: ";
	
	gotoxy(39,11);	
	cin>>dimension;
	
	if(dimension%2!= 0)
		dimension+= 1;
	
	else
		dimension+= 2;
		
	system("cls");
	
	ifstream file("Laberinto.txt" , ios::in );
	char linea;
	
	for(int i=0;i<dimension;i++)
	{
	    for(int j=0;j<dimension;j++)
		{
	        file.get(linea);
	        Lab[i][j] = linea;
	            
	        if(linea != ' ' && linea != '\n')
	        {
	            Lab[i][j] = linea;
	        }
	        	
	        else
	        {
	        	Lab[i][j]= ' ';
			}
	    }
	}

	system("color 0A");
	
	for(int i=0; i<dimension; i++)
	{
	    for(int j=0; j<dimension; j++)
	    {
	        cout <<Lab[i][j];
	    }
	    cout <<"\n";
	}

    int pila[dim][2];
    int k=0;
    int primero=0;
    int i=0;
    int j=0;
    
    while(true)
	{
        Lab[i][j]='.';
        if (Lab[i+1][j]==' ')
		{
            primero++;
            pila[primero][0]=i;
            pila[primero][1]=j;
            i++;
        }
        
        else if(Lab[i][j+1]==' ')
		{
            primero++;
            pila[primero][0]=i;
            pila[primero][1]=j;
            j++;
        }
        
        else if(Lab[i-1][j]==' ')
		{
            primero++;
            pila[primero][0]=i;
            pila[primero][1]=j;
            i--;
        }
        
        else if(Lab[i][j-1]==' ')
		{
            primero++;
            pila[primero][0]=i;
            pila[primero][1]=j;
            j--;
        }

        else
		{
            if(i==1 && j==0)
			{
                cout <<"\n No existe camino\n";
                return 0;
            }
            
            else if(i==dimension-2 && j==dimension-1)
			{
                break;
            }
            
            else
			{

            i=pila[primero][0];
            j=pila[primero][1];
            primero--;
            }
        }
    }

	cout <<"\n\t\t\Laberinto Resuelto:\n";
	
    for(int l=0;l<primero;l++)
    {
    	Lab[pila[0][0]][pila[0][0]]='1';
        Lab[pila[l][0]][pila[l][1]]='*';
    }
        
    Lab[dimension-2][dimension-1]='*';


    for (int k=0;k<dimension-1;k++)
	{
        for(int t=0;t<dimension-1;t++)
            /*textcolor(4);
            cprintf("%c ", Lab[k][t]);*/
			cout <<Lab[k][t]<<"";
        
        cout <<"\n";
    }

    return 0;
}
