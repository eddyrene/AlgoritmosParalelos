#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

void fillVector(int a, int b, int sizeHisto,vector<double> &GR)
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
		GR[i]=rand()%sizeHisto;
	}
}

void fillHistogram(int ini , int fin , vector<double> &data, std::vector<int> &histo)
{
double local_a, local_b;
int i,local_n;
int my_rank = omp_get_thread_num();
int thread_count = omp_get_num_threads();
int n=fin-ini;
local_n= n/thread_count;
local_a= ini+my_rank*local_n;
local_b=local_a+local_n;
cout<<"De "<<local_a<<" hasta  "<<local_b<<endl; 
	for(i=local_a; i<local_b; i++)
	{
		#pragma omp critical
			histo[data[i]]++; 
	}
}

void printVectord(string s , std::vector<double> v)
{
	cout<<s;
	for(int i = 0; i<v.size();i++)
	{
		cout<<v[i]<<" ";
	}
}
void printVectori(string s , std::vector<int> v)
{
	cout<<s;
	for(int i = 0; i<v.size();i++)
	{
		cout<<v[i]<<" ";
	}
}
int main(int argc, char * argv[])
{

	int thread_count = strtol(argv[1], NULL, 10);
	int tamData=100000000;
	int sizeHisto=5;
	vector<double> data;
	data.resize(tamData);
	vector<int> histograma;
	histograma.resize(sizeHisto,0);
	#pragma omp parallel num_threads(thread_count)
		fillVector(0,tamData, sizeHisto,data);
	cout<<" \n Data "<<endl;
	//printVectord("impriendo data \n ", data);
	//printVectori("\n impriendo histograma inicial \n ", histograma);
	#pragma omp parallel num_threads(thread_count)
		fillHistogram(0,tamData,data,histograma);
	printVectori("\n impriendo histograma final \n \n", histograma);
	cout<<endl;
	return 0;
}