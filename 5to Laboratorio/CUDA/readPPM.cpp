#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void print_vect(int *V, int n){
    int i;
    for (i = 0; i < n; i++)
		printf("%d ", V[i]);
}

int* ReadSizeImg(char * name)
{
    int * dim= new int[2];
    char e1;
    int fil, col;
    string line,s1;
    ifstream file(name);
    getline(file,line);
    getline(file,line);
    file>>fil>>col;
    dim[0]=fil; dim[1]=col;   
    return dim;
}
void ReadPPM(int *&Pin, char *name)
{
	int dim[2];
	int e1;
	int fil, col;
    string line,s1;
    ifstream file(name);
    getline(file,line);
    getline(file,line);
    getline(file,line);
    getline(file,line);
    int m=0;
    while(!file.eof())
    {
        file>>e1;
       // cout<<e1<<endl;
        if(!e1) break;
        Pin[m]=e1;
        m++;
    }
}

void WritePGM(int * Pout, int fil , int cols, char *name)
{
    ofstream file(name);
    file<<"P2"<<endl;
    file<<"# Function ConvertRGBtoGray @eddyrene"<<endl;
    file<<fil<<" "<<cols<<endl;
    file<<255<<endl;
    int n = fil*cols;
    int i=0;
    while(i<n)
    {
        file<<Pout[i]<<endl;
        i++;
    }
}

int main()
{
    int * Pin,* Pout;
    char * d_Pin, d_Pout;
    int * order = ReadSizeImg("prueba.ppm");
    int size = order[0]*order[1]*sizeof(int); 
    cout<<order[0]<<order[1]<<endl;
    Pin = (int *)malloc(size); 
    ReadPPM(Pin,"prueba.ppm");
    print_vect(Pin,order[0]*order[1]);

    Pout = (int *)malloc(size); 
    WritePGM(Pin, order[0],order[1],"salida.ppm");    
    
}