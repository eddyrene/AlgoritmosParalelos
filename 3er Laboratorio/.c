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


/* Read vector */

void Print_vector(
double    local_b[] /*   out  */,
int       local_n,
int       n,
char      title[],
int       my_rank,
MPI_Comm  comm) 
{
  double* b = NULL;
  int i;

  if(my_rank == 0 )
  {
     b = malloc(n*sizeof(double));
      MPI_Gather(local_b, local_n, MPI_DOUBLE, b, local_n, MPI_DOUBLE, 0, comm);
       printf("%s\n", title);
       for (i = 0; i < n; i++)
          printf("%f ", b[i]);
        printf("\n");
     free(b);
 	}
 	 else {
   MPI_Gather(local_b, local_n, MPI_DOUBLE, b, local_n, MPI_DOUBLE, 0, comm);
 }
}

void Read_vector(

double 	 	local_a[] /*   out  */,
int  		local_n,
int 		n,
int			my_rank,
MPI_Comm 	comm) 
{
	double* a = NULL;
	int i;

	if (my_rank == 0) 
	{

		a = malloc(n*sizeof(double));
		printf("Leyendo Vector \n");
		for (i = 0; i < n; i++)
			a[i] = rand() %10;	
		MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n,MPI_DOUBLE, 0, comm);
		free(a);
	} 
	else 
	{
		MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n,MPI_DOUBLE, 0, comm);
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


#define DIM 64

int main(int argc, char *argv[])
{

      int i, j, n; 
      int nlocal;        /* Number of locally stored rows of A */ 
      double *fb;
      double a[DIM*DIM], b[DIM], x[DIM];     /* Will point to a buffer that stores the entire vector b */ 
      int npes, myrank; 
      //MPI_Status status; 

     // printf( " esto debe imprimirse una vez \n");


      MPI_Init(&argc,&argv);


     n=DIM;
     /* Get information about the communicator */ 
     MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
     MPI_Comm_size(MPI_COMM_WORLD, &npes);  
     nlocal = n/npes; 



     local_a = a + my_rank*local_n*h;
	local_b = local_a + local_n*h;
	local_int = Trap(local_a, local_b, local_n, h);

	  //int n =size;
	int local_n = n/numtasks;
	int local_m = n/numtasks;

     // i=0;
    if (my_rank == 0) 
	{
		printf("multiplication Matriz vector\n");

		for(i =0;i<nlocal;i++)
		{
			//int j=0;
			for(j =0;j<n;j++)
			{
				a[j+(i*n)]= rand() % 10;
			}

			b[i] = rand() % 10; 
		}
	}	
	else
	{
	     /* Allocate the memory that will store the entire vector b */ 
	     fb = (double*)malloc(n*sizeof(double)); 
	     /* Gather the entire vector b on each processor using MPI's ALLGATHER operation */ 
	     MPI_Allgather(b, nlocal, MPI_DOUBLE, fb, nlocal, MPI_DOUBLE, MPI_COMM_WORLD); 

	     /* Perform the matrix-vector multiplication involving the locally stored submatrix */ 
	     for (i=0; i<nlocal; i++) { 
	       x[i] = 0.0; 
	       for (j=0; j<n; j++) 
	         x[i] += a[i*n+j]*fb[j]; 
	     } 
	     i =0; 
	     printf( "%d \n", myrank);
	     int count = 0;
	     for(;i<nlocal;i++)
	     {
	     	count++;
	     	printf( "%f \n", x[i]);	
	     }
	     printf( " count of : %d is : %d \n", myrank, count);
	     //printf( "%s\n", );
	     free(fb);
 	}

     MPI_Finalize();   
}//end main 


