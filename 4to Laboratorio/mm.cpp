/*Eddy René Caceres Huacarpuma*/ 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ctime"
#include <iostream>


using namespace std;
 
 //variables globales

int n,m;
double * x;
double * y;
double * A;
int thread_count; 

 void* Hello(void* rank) {
	long my_rank = (long) rank;
	printf("Hello from thread %ld of %d\n", my_rank, thread_count);
	return NULL;
 }

void rand_vector(double x[], int n) {
   int i;
   for (i = 0; i < n; i++)
      x[i] = random()/((double) RAND_MAX);
}

void print_vector(double x[], int n) 
{
	for(int i =0 ; i< n; i++)
		cout<<x[i]<<" ";
	cout<<endl;
}
void  rand_matrix( double * A, int m , int n)
{
	for(int i =0;i<m*n;i++)
		A[i]= random()/((double) RAND_MAX);	     //
}  /* Read_matrix */	
void  print_matrix( double * A, int m , int n)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout<<A[j+i*m]<<" ";
		cout <<endl;
	}
}
void *Pth_mat_vect(void* rank) {
   long my_rank = (long) rank;
   int i;
   int j; 
   int local_m = m/thread_count; 
   int my_first_row = my_rank*local_m;
   int my_last_row = (my_rank+1)*local_m - 1;

#  ifdef DEBUG
   printf("Thread %ld > my_first_row = %d, my_last_row = %d\n",
         my_rank, my_first_row, my_last_row);
#  endif

   for (i = my_first_row; i <= my_last_row; i++) {
      y[i] = 0.0;
      for (j = 0; j < n; j++)
          y[i] += A[i*n+j]*x[j];
   }

   return NULL;
} 

 int main(int argc, char* argv[]) {

 	 m = n = 16384;
 	 x = new double[m];
 	 y = new double[m];
 	 A = new double[m*n];
 	 double start, finish;

	 long thread;  
	 pthread_t* thread_handles;

	 thread_count = strtol(argv[1], NULL, 10);
	 thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));

	cout<<"vector "<<endl;
	rand_vector(x, n);
	//print_vector(x, n);

	cout<<"matriz"<<endl;
	rand_matrix(A, n, m);
	//print_matrix(A, n, m);

	
	start = clock();
	 for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL,Pth_mat_vect, (void*) thread);

	 //printf("Hello from the main thread\n");

	 for (thread = 0; thread < thread_count; thread++)
	 	pthread_join(thread_handles[thread], NULL);
	 finish=clock();
	cout<<"resultado"<<endl; 
	print_vector(y,n);	 

	cout<<"tiempo de ejecucion "<<finish-start/double(CLOCKS_PER_SEC)*1000<<endl;

	 free(thread_handles);
	 delete [] A; 
	 delete [] x; 
	 delete [] y;
	 return 0;

 }

