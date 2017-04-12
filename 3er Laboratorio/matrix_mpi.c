#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

void Mat_vect_mult(
	double local_A[],
	double local_x[],
	double local_y[],
	int local_m,
	int n,
	int local_n,
	MPI_Comm comm )
{
   double* x;
   int local_i, j;
   int local_ok ;
   local_ok= 1;
  x = malloc(n*sizeof(double));
  if( x == NULL) 
    local_ok =0 ;
  MPI_Allgather(local_x, local_n, MPI_DOUBLE, x, local_n, MPI_DOUBLE, comm);
  for (local_i = 0; local_i < local_m; local_i++) 
  {
  	local_y[local_i] = 0.0;
  	for (j = 0; j < n; j++)
  		local_y[local_i] += local_A[local_i*n+j]*x[j];
  }
  free(x);
}

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
int main(void)
{
	int numtasks, rank; /*sendcount, recvcount, source;*/
	int size =1; 
	double matriz[16] ={1.0, 2.0, 3.0, 4.0 , 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
	double vector[4] = {1.0, 2.0, 3.0, 4.0};
  	double result[4]={0,0,0,0};
  	/*float sendbuf[SIZE][SIZE] = {
      {1.0, 2.0, 3.0, 4.0},
      {5.0, 6.0, 7.0, 8.0},
      {9.0, 10.0, 11.0, 12.0},
      {13.0, 14.0, 15.0, 16.0}  };*/
  	//double recvbuf[SIZE];
	MPI_Init(NULL,NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &	numtasks);
  int n =size;
	int local_n = 16/numtasks;
	int local_m = 4/numtasks;


		//Print_vector(result,local_n, n,"resultado", rank, MPI_COMM_WORLD);
  		Mat_vect_mult(matriz,vector, result,local_m,n,local_n,MPI_COMM_WORLD);
  		

  		/*	for (int j =0 ; j< 4 ;j++ )
  				printf("%f ", result[j]);
  			printf("\n");
  		*/
  		//Print_vector(result,local_n, n,"resultado", rank, MPI_COMM_WORLD);

	MPI_Finalize();
	/* code */
	return 0;
}