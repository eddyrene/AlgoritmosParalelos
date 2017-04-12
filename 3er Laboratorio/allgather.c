#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>


void print_serial(double v[] , int t)
{
	int i=0;
	for(i=0;i<t;i++)
	{
		printf("%f  \n",v[i]);
	}
}

void llenar_mat(double m[][], int c, int f)
{
	for(int i =0;i<f;i++)
		for(int j =0;j<c;j++)
		{
			m[i][j]= rand() % 100;
		}
}
int main(void)
{
	int my_rank, comm_sz;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	double a[100][25], b[100], cpart[25], ctotal[100];
	int i,k;
	for(i=0;i<25;i++)
	{
   		cpart[i]=0;
   		for(k=0;k<100;k++)
	   {
	      cpart[i]=cpart[i]+a[k][i]*b[k];
	   }
	}
	print_serial(cpart,25);
	//print_serial();

	MPI_Allgather(cpart,25,MPI_INT,ctotal,25,MPI_INT,MPI_COMM_WORLD);
	MPI_Finalize();
		return 0;
} 