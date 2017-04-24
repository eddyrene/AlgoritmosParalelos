/*Eddy René Caceres Huacarpuma*/ 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ctime"
#include <iostream>


using namespace std;
 
 //variables globales

long long n;
int flag;
double sum;
int thread_count; 
pthread_mutex_t mutex;


 void* Thread_sum(void* rank) {
	 long my_rank = (long) rank;
	 double factor;

	 long long i;
	 cout<<"n: "<<n<<endl;
	 long long my_n = n/thread_count;

	 long long my_first_i = my_n*my_rank;

	 long long my_last_i = my_first_i + my_n;

	 if (my_first_i % 2 == 0) /* my first i is even */
	 	factor = 1.0;
	 else /* my first i is odd */
	 	factor =- 1.0;
	cout<<"se estas "<<endl;
	for (i = my_first_i; i < my_last_i; i++, factor =- factor) {
		sum += factor/(2*i+1);
		}
	return NULL;
}
void* Thread_sum_mutex(void* rank) {
   long my_rank = (long) rank;
   double factor;
   long long i;
   long long my_n = n/thread_count;
   long long my_first_i = my_n*my_rank;
   long long my_last_i = my_first_i + my_n;
   double my_sum = 0.0;

   if (my_first_i % 2 == 0)
      factor = 1.0;
   else
      factor = -1.0;

   for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
      my_sum += factor/(2*i+1);
   }
   pthread_mutex_lock(&mutex);

   sum += my_sum;
   pthread_mutex_unlock(&mutex);

   return NULL;
}  /* Thread_sum */

void* Thread_sum_bs(void* rank) {
   long my_rank = (long) rank;
   double factor, my_sum = 0.0;
   long long i;
   long long my_n = n/thread_count;
   long long my_first_i = my_n*my_rank;
   long long my_last_i = my_first_i + my_n;

   if (my_first_i % 2 == 0)
      factor = 1.0;
   else
      factor = -1.0;

   for (i = my_first_i; i < my_last_i; i++, factor = -factor) 
      my_sum += factor/(2*i+1);  
   
   while (flag != my_rank);
   sum += my_sum;  
   if (my_rank < thread_count-1)
      flag++;

   return NULL;
}  /* Thread_sum */

 int main(int argc, char* argv[]) {

 	 //sum =0;
 	 n=100000000;
 	 double start, finish;

	 long thread;  
	 pthread_t* thread_handles;

	 thread_count = strtol(argv[1], NULL, 10);
	 thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));

	
	start = clock();
	 for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL,Thread_sum, (void*) thread);

	 //printf("Hello from the main thread\n");

	 for (thread = 0; thread < thread_count; thread++)
	 	pthread_join(thread_handles[thread], NULL);
	 finish=clock();
	 sum = 4.0*sum;
	cout<<"resultado : "<<sum<<endl; 

	cout<<"tiempo de ejecucion "<<(finish-start)/double(CLOCKS_PER_SEC)<<endl;
	 free(thread_handles);
	 return 0;

 }

