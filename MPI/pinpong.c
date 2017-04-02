#include <stdio.h> 
#include <string.h> 
#include "mpi.h"
int main(int argc, char **argv) 
{
  int  rank, size, tag = 99;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int ping = 0;
  
  while(ping<10)
  {
    if (rank == ping %2 )
    {
        ping++;
        MPI_Send(&ping, 2, MPI_INT, (rank+1)%2, tag, MPI_COMM_WORLD);
        printf( "Enviado de  %d  a  %d   :  %d \n", rank , (rank+1)%2,  ping);
    }
    else 
    {   
      MPI_Recv(&ping, 2, MPI_INT, (rank+1)%2, tag, MPI_COMM_WORLD, &status);
    }
  }
  MPI_Finalize();
}