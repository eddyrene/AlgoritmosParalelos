#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

#define TILE_WIDTH 32

void fillMatrix(int* a, int n)
{
   int i;
   for (i = 0; i < n*n; ++i)
        a[i] = 10;//rand()%5;
}

__global__ 
void matrixAdition(int *c, int *a, int *b,int n) 
{
    int ij = threadIdx.x + blockDim.x * blockIdx.x;
		if(ij<(n*n))
			c[ij] = a[ij] + b[ij];
}

__global__ 
void matrixAditionRow(int *c, int *a, int *b,int n) 
{
   	int ij = threadIdx.x + blockDim.x * blockIdx.x;
   //	if(blockDim.x != 0)
   	//printf("%d  salida\n", ij);
	for(int i =0 ;i<n;i++)
	{
		if(ij<n)
			c[ij*n+i] = a[ij*n+i] + b[ij*n+i];
	}
}

__global__ 
void matrixAditionCol(int *c, int *a, int *b,int n) 
{
   	int ij = threadIdx.x + blockDim.x * blockIdx.x;
	for(int i =0 ;i<n;i++)
	{
		if(ij<n)
			c[ij+n*i] = a[ij+n*i] + b[ij+n*i];
	}
}
__global__ 
void matrixMulti(int *c, int *a, int *b,int n) 
{
    int row = blockIdx.y * blockDim.y + threadIdx.y ; 
    int col = blockIdx.x * blockDim.x + threadIdx.x ;
    if ((row <n) && (col<n))
    {
		int suma=0;
        for(int i=0;i<n;++i)
        {
        	suma+=a[row*n+i]*b[i*n+col];
        }
        c[row*n+col] = suma;	
    } 
}
__global__ void MatrixMulKernel(int * d_P, int * d_M, int* d_N,int Width) 
{
	__shared__ int Mds[TILE_WIDTH][TILE_WIDTH];
	__shared__ int Nds[TILE_WIDTH][TILE_WIDTH];
	int bx = blockIdx.x; int by = blockIdx.y;
	int tx = threadIdx.x; int ty = threadIdx.y;
	// Identify the row and column of the d_P element to work on
	int Row = by * TILE_WIDTH + ty;
	int Col = bx * TILE_WIDTH + tx;
	int Pvalue = 0;
	// Loop over the d_M and d_N tiles required to compute d_P element
	for (int ph = 0; ph < Width/TILE_WIDTH; ++ph) 
	{
		// Collaborative loading of d_M and d_N tiles into shared memory
		Mds[ty][tx] = d_M[Row*Width + ph*TILE_WIDTH + tx];
		Nds[ty][tx] = d_N[(ph*TILE_WIDTH + ty)*Width + Col];
		__syncthreads();
		for (int k = 0; k < TILE_WIDTH; ++k)
		{
	 		Pvalue += Mds[ty][k] * Nds[k][tx];
		}
	 	__syncthreads();
	}
	d_P[Row*Width + Col] = Pvalue;
}

void printMatrix(string s, int *a , int tam){
	cout<<s;
	for(int i=0;i<tam;i++)
	{
		for(int j=0;j<tam;j++)
		{
			cout<<a[i*tam+j]<<" ";
		}
		cout<<endl;
	}
}

int main(int argc, char *argv[])
{
	srand (time(NULL));
	int  N= strtol(argv[1], NULL, 10);
	//cout<<N<<endl; return 1;
	int THREADS_PER_BLOCK =32;	
	int *a, *b, *c; // host copies of a, b, c
	int *d_a, *d_b, *d_c; //device copies of a,b,c
	//int size = N*N*sizeof(int);
	int size=N*N*sizeof(int);
	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);

	a = (int *)malloc(size); 
	fillMatrix(a, N);
	b = (int *)malloc(size); 
	fillMatrix(b, N);
	c = (int *)malloc(size);
	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
	/*int blocks= (N*N + THREADS_PER_BLOCK -1)/THREADS_PER_BLOCK;
	int blocks2= (N + THREADS_PER_BLOCK -1)/THREADS_PER_BLOCK;
	cout<<"blocks : \n"<<blocks2<<"\n threds: \n "<<THREADS_PER_BLOCK<<endl; */

	int blocks= (N + THREADS_PER_BLOCK -1)/THREADS_PER_BLOCK;
	dim3 dimGrid(blocks, blocks, 1);
	dim3 dimBlock(THREADS_PER_BLOCK,THREADS_PER_BLOCK, 1);
	cout<<"blocks : \n"<<blocks<<"\n threds: \n "<<THREADS_PER_BLOCK<<endl; 
	cudaEvent_t start, stop;
	float elapsedTime;
	cudaEventCreate(&start);
	cudaEventRecord(start,0);
		//matrixAdition<<<blocks,THREADS_PER_BLOCK>>>( d_c, d_a, d_b,N);
		//matrixAditionRow<<<blocks2,THREADS_PER_BLOCK>>>(d_c, d_a, d_b,N);
		//matrixMulti<<<blocks2,THREADS_PER_BLOCK>>>(d_c, d_a, d_b,N);
		//matrixAditionCol<<<blocks2,THREADS_PER_BLOCK>>>( d_c, d_a, d_b,N);
		matrixMulti<<<dimGrid,dimBlock>>>(d_c, d_a, d_b, N);
		//MatrixMulKernel<<<dimGrid,dimBlock>>>(d_c, d_a, d_b, N);
	cudaEventCreate(&stop);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start,stop);
	printf("Elapsed time : %f ms\n" ,elapsedTime);
	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

	//printMatrix("Printing Matrix A \n",a,N);
	//printMatrix("Printing Matrix B \n",b,N);
	//printMatrix("Printing Matrix C \n",c,N);
	free(a); free(b); free(c);
	cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
	return 0;
}
