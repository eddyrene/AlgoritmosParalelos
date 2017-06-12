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

   for (i = my_first_row; i <= my_last_row; i++) {
      y[i] = 0.0;
      for (j = 0; j < n; j++)
          y[i] += A[i*n+j]*x[j];
   }

   return NULL;
} 

 int main(int argc, char* argv[]) {

 	 m = 8000000;
 	 n = 8;
 	 x = new double[n];
 	 y = new double[m];
 	 A = new double[m*n];
 	 struct timespec start, finish;
	double elapsed;

	 long thread;  
	 pthread_t* thread_handles;

	 thread_count = strtol(argv[1], NULL, 10);
	 //cout<<"numero de thread: "<< thread_count<<endl;
	 thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));

	//cout<<"vector "<<endl;
	rand_vector(x, n);
	//print_vector(x, n);

	//cout<<"matriz"<<endl;
	rand_matrix(A, m, n);
	//print_matrix(A, n, m);

	
	clock_gettime(CLOCK_MONOTONIC, &start);
	 for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL,Pth_mat_vect, (void*) thread);

	 //printf("Hello from the main thread\n");

	 for (thread = 0; thread < thread_count; thread++)
	 	pthread_join(thread_handles[thread], NULL);
	 
	clock_gettime(CLOCK_MONOTONIC, &finish);
	//cout<<"resultado"<<endl; 
	//print_vector(y,m);	 
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	cout<<"tiempo de ejecucion "<<elapsed<<endl;

	 free(thread_handles);
	 delete [] A; 
	 delete [] x; 
	 delete [] y;
	 return 0;

 }

