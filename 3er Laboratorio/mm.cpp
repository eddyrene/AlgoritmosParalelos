



#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void Read_vector(
        //int    m , int n , 
         int *   local_x  /* out */, 
         int    local_n    /* in  */, 
         int    my_rank    /* in  */,
         int    p          /* in  */) {

    int   i;
    int *  temp =new int[p*local_n];
    if (my_rank == 0) {
        for (i = 0; i < p*local_n; i++) 
            temp[i]=i;
    }
    MPI_Scatter(temp, local_n, MPI_FLOAT, local_x, local_n, MPI_FLOAT,
        0, MPI_COMM_WORLD);
} 

/**********************************************************************/
void Print_vector(
         //int    m , int n , 
         int *  local_y  /* in */, 
         int    local_m    /* in */, 
         int    my_rank    /* in */,
         int    p          /* in */) {

    int   i;
    int * temp=new int[p*local_m];

    MPI_Gather(local_y, local_m, MPI_FLOAT, temp, local_m, MPI_FLOAT,
        0, MPI_COMM_WORLD);

    if (my_rank == 0) {
       
        for (i = 0; i < p*local_m; i++)
            cout<<temp[i]<<" ";
        cout<<endl;
    } 
}  /* Print_vector */

int *  Read_matrix(
         int   f , int c ,  
         int *             local_A /* out */, 
         int             local_m  /* in  */, 
         int             n        /* in  */,
         int             my_rank  /* in  */, 
         int             p        /* in  */) 

  {
    int  i, j;
   /// cout<<"Se creo"<<endl;
    int *  temp;
    if (my_rank == 0) {
         temp= (int*)malloc(f*c*sizeof(int));
       // printf(" Generando Matriz \n");
        for (i = 0; i < f*c; i++) 
            temp[i]=i;
    }
    return temp;
     //
}  /* Read_matrix */


void Print_matrix(
        int   f , int c ,  
         int *           local_A   /* in */, 
         int             local_m    /* in */, 
         int             n          /* in */,
         int             my_rank    /* in */,
         int             p          /* in */) {

    int   i, j;
    int *  temp= (int*)malloc(f*c*sizeof(int));
    MPI_Gather(local_A, local_m*f, MPI_FLOAT, temp,local_m*f, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        for (i = 0; i < f; i++) {
            for (j = 0; j < c; j++)
                cout<<temp[j+i*f]<<" ";
            printf("\n");
        }
    } 
} 


void printArray (int *row, int nElements) {
    int i;
    for (i=0; i<nElements; i++) {
        printf("%d ", row[i]);
    }
    printf("\n");
}

void Mat_vect_mult(
                  int * local_A,
                  int * local_x,
                  int * x,
                  int * local_y,
                  int local_m,
                  int n,
                  int local_n,
                  int mr,
                  MPI_Comm comm )
{

double local_start, local_finish, local_elapsed, elapsed;

int i, j;
MPI_Allgather(local_x, local_n, MPI_INT, x, local_n, MPI_INT, comm);

MPI_Barrier(comm);
local_start = MPI_Wtime();

for (i = 0; i < local_m; i++) 
{
local_y[i] = 0.0;
for (j = 0; j < n; j++)
  local_y[i] += local_A[i*n+j]*x[j];
}

local_finish = MPI_Wtime();
local_elapsed = local_finish - local_start;

MPI_Reduce  (&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

if (mr == 0)
        printf("tiempo de ejecuciomn = %e segundos\n", elapsed);
}


/* Codigo Eddy Rene Caceres Huacarpuma */ 

int main(int argc, char* argv[]) 
{
    int             my_rank;
    int             p;
    int *           local_A; 
    int *           local_x;
    int             local_m, local_n;
    int             m, n;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    m=n=15; 

    int     *      global_x = (int*)malloc(sizeof(int) * m);
    int     *      local_y = (int*)malloc(sizeof(int) * m);
    local_m = m/p;
    local_n = n/p;
    int *  matriz;
    srand (time(NULL));

    /*funcion para medir tiempo */
    /* Codigo a ser medido */

    if (my_rank == 0) {
        matriz = Read_matrix(m,n,local_A, local_m, n, my_rank, p);
        //printArray(matriz, m*n);
    }
    //cout<<endl;
    local_A = (int*)malloc(sizeof(int) * local_m*m);
    if (local_A == NULL) {
        perror("Error in malloc 3");
        exit(1);
    }
    if(MPI_Scatter(matriz, local_m*m, MPI_INT, local_A ,local_m*m, MPI_INT, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
    {
        perror("Scatter error");
        exit(1);
    }        
    //Print_matrix(m,n,local_A, local_m, n, my_rank, p);
    local_x =  (int*)malloc(sizeof(int)*m);
    Read_vector(local_x, local_n, my_rank, p);
    //cout<<endl;
    //Print_vector(local_x, local_n, my_rank,p );
    //cout<<endl;
    Mat_vect_mult(local_A, local_x,global_x, local_y, local_m , n,local_n ,my_rank, MPI_COMM_WORLD );
    //
    
    //Print_vector(local_y, local_m,my_rank,p);






    
    MPI_Finalize();

    return 0;
    
}