#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

double genRandom(double li, double ls)
{
	//srand (time(NULL));
	return li + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(ls-li)));
}

int main(int argc, char * argv[])
{
	int thread_count = strtol(argv[1], NULL, 10);
	srand (time(NULL));
	long long int number_of_tosses=100000000;
	int number_in_circle = 0;	
	long long int  toss;
	double x, y , dist;
	//cout<<"este es el numero de threads"<< thread_count;
	//int parts = number_of_tosses/ thread_count;
	//cout<<"estas son las parts"<<parts<<endl;
	#pragma omp parallel for num_threads(thread_count) \
			shared(number_of_tosses) private(x,y,dist)  \
			reduction(+: number_in_circle) 
			for(toss = 0; toss < number_of_tosses; toss++) 
			{
				x = genRandom(-1,1);
				//cout<<"p   "<<omp_get_thread_num<<endl;	 
				y = genRandom(-1,1); 
				//cout<<"s   "<<omp_get_thread_num<<endl;
				dist = sqrt(x*x+y*y);
				if ( dist<= 1)
				{
					int my_rank = omp_get_thread_num();
					int thread_count = omp_get_num_threads();
					//cout<<my_rank <<"  "<<thread_count<<endl;
					//cout<<" acc po "<<number_in_circle<<endl;
					number_in_circle=number_in_circle+1;
					//cout<<" acc po "<<number_in_circle<<endl;
				}
				//printf("con %d obtuve %d \n" , omp_get_thread_num(),number_in_circle  );
			}
	printf("numeros en circulo %d \n", number_in_circle);
	double pi_estimate = 4*number_in_circle/((double) number_of_tosses);
	cout<<pi_estimate<<endl;
}