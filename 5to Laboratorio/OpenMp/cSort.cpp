#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

void fillVector(int a, int b, double *GR, int size)
{
	double local_a, local_b;
	int i,local_n;
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	int n=b-a;
	local_n= n/thread_count;
	local_a= a+my_rank*local_n;
	local_b=local_a+local_n;
	for(i=local_a; i<local_b; i++)
	{	
		GR[i]=rand()%size;
	}
}
void printVectord(string s , double v[], int size)
{
	cout<<s;
	for(int i = 0; i<size;i++)
	{
		cout<<v[i]<<" ";
	}
}
void printVectori(string s , int v[], int size)
{
	cout<<s;
	for(int i = 0; i<size;i++)
	{
		cout<<v[i]<<" ";
	}
}

double * Count_sort(double *a, int n, int thread_count) 
{
	int i, j, count;
	double* temp = (double*)malloc(n*sizeof(double));
	 #pragma omp parallel for num_threads(thread_count) \
		default(none) private(i, j,count) shared(a,n,temp)
	for (i = 0; i < n; i++) {
		count = 0;
		for ( j = 0; j < n; j ++)
			if (a [j] < a[i])
				count ++;
			else if (a[j] == a [i ] && j < i)
				count ++;
		temp[ count ] = a[i];
	}

	#pragma omp parallel for num_threads(thread_count)
		for(int i =0;i<n;i++)
			a[i]=temp[i];

	//std::memcpy(a, temp , n*sizeof(int) );
	//a=temp;
	return temp;
	free( temp);
	/* Count sort */
}
int main(int argc, char * argv[])
{
	int thread_count = strtol(argv[1], NULL, 10);
	int tamData=50000;
	double data[tamData];

	double start_time = omp_get_wtime();
	#pragma omp parallel num_threads(thread_count)
		fillVector(0,tamData,data,tamData);
	//printVectord("impriendo data \n ", data, tamData);
	double * salida = Count_sort(data, tamData, thread_count);	
	double time = omp_get_wtime() - start_time;
	cout<<"tiempo total "<< time<<endl;
	//printVectord("vector ordenado \n ", salida, tamData);
}
