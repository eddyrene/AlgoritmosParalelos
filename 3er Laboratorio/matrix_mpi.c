
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024
//typedef double mat 4[SIZE][SIZE];


void Print_vector(
  double    local_b[],    /*   int  */
  int       local_n,      /*   int  */
  int       n,        /*   int  */
  int       my_rank,      /*   int  */
  MPI_Comm  comm    )       /*   int  */
  
  {
  double* b = NULL;
  int i;

  if(my_rank == 0 )
  {
     b = malloc(n*sizeof(double));
      MPI_Gather(local_b, local_n, MPI_DOUBLE, b, local_n, MPI_DOUBLE, 0, comm);
       printf("Impriendo Vector! \n " );
       for (i = 0; i < n; i++)
          printf("%f ", b[i]);
        printf("\n");
     free(b);
  }
  
  else 
    MPI_Gather(local_b, local_n, MPI_DOUBLE, b, local_n, MPI_DOUBLE, 0, comm);
  
}
/*
	void Read_vector(
	double    local_a[] ,
	int     local_n,
	int     n,
	int     my_rank,
	MPI_Comm  comm) 
	{
	  double* a = NULL;
	  int i;

	  if (my_rank == 0) 
	  {

	    a = (double*)malloc(n*sizeof(double));
	    printf("Generando Vector \n" );
	    for (i = 0; i < n; i++)
	      a[i]=  rand() % 10;
	    MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n,MPI_DOUBLE, 0, comm);
	    free(a);
	  } 
	  else 
	  {
	    MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n,MPI_DOUBLE, 0, comm);
	  }

	}
*/
void Read_vector(
         char*  prompt     /* in  */,
         float  local_x[]  /* out */, 
         int    local_n    /* in  */, 
         int    my_rank    /* in  */,
         int    p          /* in  */) {

    int   i;
    float temp[SIZE];

    if (my_rank == 0) {
        printf("%s\n", prompt);
        for (i = 0; i < p*local_n; i++) 
            temp[i]=rand() % 10;
    }
    MPI_Scatter(temp, local_n, MPI_flo, local_x, local_n, MPI_DOUBLE,
        0, MPI_COMM_WORLD);

}  /* Read_vector */
void Read_matrix(
         double        local_A [] /* out */, 
         int             local_m  /* in  */, 
         int             n        /* in  */,
         int             my_rank  /* in  */, 
         int             p        /* in  */) 

  {
    int  i, j;
    double* temp = NULL;

    /* Fill dummy entries in temp with zeroes */
    /*for (i = 0; i < p*local_m; i++)
        for (j = n; j < SIZE; j++)
            temp[i+(j*p*local_m)] = 0.0;*/

    if (my_rank == 0) {

      temp= malloc(n*sizeof(double));
        printf(" Generando Matriz \n");
        for (i = 0; i < p*local_m; i++) 
            for (j = 0; j < n; j++)
            {
              int ra= rand() % 10;
                temp[j+(i*p*local_m)]=ra; 
                //printf("Impriendo %d  : %d  \n" , temp[j+(i*p*local_m)], ra);
;            }
      MPI_Scatter(temp, local_m*SIZE, MPI_DOUBLE, local_A,local_m*SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      free(temp);
    }
    else
      MPI_Scatter(temp, local_m*SIZE, MPI_DOUBLE, local_A,local_m*SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   // MPI_Scatter(a, local_n, MPI_DOUBLE, local_a, local_n,MPI_DOUBLE, 0, comm);

}  /* Read_matrix */

void Print_matrix(
        // char*           title      /* in */, 
         double          local_A []   /* in */, 
         int             local_m    /* in */, 
         int             n          /* in */,
         int             my_rank    /* in */,
         int             p          /* in */) {

    int   i, j;
    double temp[SIZE* SIZE];

    MPI_Gather(local_A, local_m*SIZE, MPI_DOUBLE, temp,local_m*SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        //printf("%s\n", title);
        for (i = 0; i < p*local_m; i++) {
            for (j = 0; j < n; j++)
                printf("%4.1f ", temp[j+(i*p*local_m)]);
            printf("\n");
        }
    } 
}  /* Print_matrix */


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
  x = malloc(SIZE*sizeof(double));
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

int main(int argc, char* argv[]) 
{
    int               my_rank;
    int             p;
    double          local_A[SIZE * SIZE]; 
    double           global_x[SIZE];
    double         local_x[SIZE];
    double           local_y[SIZE];
    int             m, n;
    int             local_m, local_n;


  MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        printf("Enter the order of the matrix (m x n)\n");
        scanf("%d %d", &m, &n);
    //m=8; 
    //n=8;
    }
    
  	//MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
   //MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_m = m/p;
    local_n = n/p;

   //Read_matrix(local_A, local_m, n, my_rank, p);
   //Print_matrix(local_A, local_m, n, my_rank, p);

   // Read_vector(local_x, local_n,n ,my_rank,MPI_COMM_WORLD);

    Read_vector("Enter the vector", local_x, local_n, my_rank, p, m , n);

    //Print_vector(local_x, local_n, n,my_rank,MPI_COMM_WORLD);


    //Mat_vect_mult(local_A, local_x, local_y, local_m , n,local_n ,MPI_COMM_WORLD );
    
   // Print_vector(local_y, local_m, n ,my_rank, MPI_COMM_WORLD);
   // printf("Resultado de la multiplicacion \n");
    MPI_Finalize();

  return 0;
}