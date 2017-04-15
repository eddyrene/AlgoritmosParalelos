#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


void Read_vector(

double 	 	local_a[] /*   out  */,
int  		local_n,
int 		n,
char 		vec_name[],
int			my_rank,
MPI_Comm 	comm) 
{
	double* a = NULL;
	int i;

	if (my_rank == 0) 
	{

		a = malloc(n*sizeof(double));
		printf("Enter the vector %s\n", vec_name);
		for (i = 0; i < n; i++)
		scanf("%lf", &a[i]);	
		MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n,MPI_DOUBLE, 0, comm);
		free(a);
	} 
	else 
	{
		MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n,MPI_DOUBLE, 0, comm);
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
int main(void)
{
	int numtasks, rank, sendcount, recvcount, source;
	int size =4;
	double myvect[SIZE] = {1.0, 2.0, 3.0, 4.0};
  	/*float sendbuf[SIZE][SIZE] = {
      {1.0, 2.0, 3.0, 4.0},
      {5.0, 6.0, 7.0, 8.0},
      {9.0, 10.0, 11.0, 12.0},
      {13.0, 14.0, 15.0, 16.0}  };*/
  	double recvbuf[SIZE];

	MPI_Init(NULL,NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  	int n =SIZE;
	int local_n = n/numtasks;
	int local_m = 4;

	char name[] = {"eddyvector"};

  	//if (numtasks == SIZE)
  	//{
  		Read_vector(myvect,local_n, n,name, rank, MPI_COMM_WORLD);
  		Print_vector(myvect,local_n, n,name, rank, MPI_COMM_WORLD);
  //	}
	MPI_Finalize();
	/* code */
	return 0;
}