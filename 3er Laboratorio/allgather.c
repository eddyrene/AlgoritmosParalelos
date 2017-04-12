#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int ff =  20; 
int cc = 5 ;

void print_serial(double v[] , int t)
{
	int i=0;
	for(i=0;i<t;i++)
	{
		printf("%f  \n",v[i]);
	}
}

void llenar(double m[][cc], double b[], int f , int c)
{
	int i=0;
	for(i =0;i<f;i++)
	{
		int j=0;
		for(j =0;j<c;j++)
		{
			m[i][j]= rand() % 10;
		}

		b[i] = rand() % 10; 
	}
}


int main(void)
{
	int my_rank, comm_sz;
	double a[ff][cc], b[ff], cpart[cc], ctotal[ff];
	llenar(a,b, ff, cc);
	print_serial(cpart,cc);

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	int i,k;
	
	for(i=0;i<cc;i++)
	{
   		cpart[i]=0;
   		for(k=0;k<ff;k++)
	   {
	      cpart[i]=cpart[i]+a[k][i]*b[k];
	   }
	}
	
	//print_serial();

	MPI_Allgather(cpart,5,MPI_INT,ctotal,5,MPI_INT,MPI_COMM_WORLD);
	MPI_Finalize();

	printf("%s \n", "aqui");
		//print_serial(cpart,cc);

		return 0;
} 