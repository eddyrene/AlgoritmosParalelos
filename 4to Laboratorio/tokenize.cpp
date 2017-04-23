

/*Eddy René Caceres Huacarpuma*/ 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ctime"
#include <iostream>
#include <string.h>
#include <semaphore.h>

int thread_count; 
const int MAX = 1000;
using namespace std;
sem_t* sems;
void *Tokenize(void* rank) {
   long my_rank = (long) rank;
   int count;
   int next = (my_rank + 1) % thread_count;
   char *fg_rv;
   char my_line[MAX+1];
   char *my_string, *saveptr; 

   /* Force sequential reading of the input */
   sem_wait(&sems[my_rank]);
   fg_rv = fgets(my_line, MAX, stdin);
   sem_post(&sems[next]);
   while (fg_rv != NULL) {
      printf("Thread %ld > my line = %s", my_rank, my_line);

      count = 0;
      my_string = strtok_r(my_line, " \t\n", &saveptr);
      while ( my_string != NULL ) {
         count++;
         printf("Thread %ld > string %d = %s\n", my_rank, count, my_string);
         my_string = strtok_r(NULL, " \t\n", &saveptr);
      }
      sem_wait(&sems[my_rank]);
      fg_rv = fgets(my_line, MAX, stdin);
      sem_post(&sems[next]);
   }

   return NULL;
}  /* Tokenize */

int main(int argc, char* argv[]) {

    long thread;  
    pthread_t* thread_handles;

    thread_count = strtol(argv[1], NULL, 10);    
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
    sems = (sem_t *)malloc(thread_count*sizeof(sem_t));
      sem_init(&sems[0], 0, 1);
    for (thread = 1; thread < thread_count; thread++)
      sem_init(&sems[thread], 0, 0);


   cout<<"Ingrese texto"<<endl;
    for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,Tokenize, (void*) thread);
  
    
    for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);
    

   for (thread=0; thread < thread_count; thread++)
      sem_destroy(&sems[thread]);

    free(sems);
    free(thread_handles);
    return 0;

 }
