#include <iostream>
#include <vector>

using namespace std;

//#define SM (CLS / sizeof (double))

typedef vector<int> array;
typedef vector<vector<int> > matriz;


void imprimir(matriz &v, int a , int b)
{
	for(int i=0;i<a;i++)
	{
		for(int j=0;j<b;j++)
			cout<<v[i][j]<<"\t";
		cout<<endl;
	}
}

void crear_matriz(matriz &v, int a , int b)
{
	v.resize(a);
	for(int i=0;i<a;i++)	
		v[i].resize(b);
}
void llenar_matriz(matriz &v, int a , int b)
{
	for(int i=0;i<a;i++)
	{
		for(int j=0;j<b;j++){
			cout<<"M["<<i<<"]["<<j<<"]: ";
				 cin>> v[i][j];}
	}
}
void llenar_ceros(matriz &v, int a , int b)
{
	for(int i=0;i<a;i++)
	{
		for(int j=0;j<b;j++){
				v[i][j]=0; }
	}

}
matriz multiplicacion(matriz &A,int m,int n, matriz &B ,int o)
{
	matriz C;
	crear_matriz(C,m,o);
	llenar_ceros(C,m,o);			
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			for(int k=0;k<o;k++)
				C[i][j]+=A[i][k]*B[k][j];

	return C;
}

matriz multiplicacion2(matriz &A,int N, matriz &B)
{
	double SM=32;
    matriz res;
	crear_matriz(res,N,N);
	llenar_ceros(res,N,N);
	for (int i1 = 0; i1 < N/SM; i1 += SM)
		for (int j1 = 0; j1 < N/SM; j1 += SM)
			for ( int k1 = 0; k1 <N/SM; k1 += SM)
				for (int i = i1; i<i1+SM&&i<N;i++)
					for	(int j=j1;j<j1+SM&&j<N;j++)
						for	(int k=k1;k<k1+SM&&k<N;k++)
							res[i][j]+=A[i][k]*B[k][j];
	return res;
}	

int main()
{
	int m,n,o;
	matriz v,t;
	// ------------primera matriz ------------
	cout<<"Ingrese tamaño de la matriz 1"<<endl;	
	cin>>m>>n;
	crear_matriz(v,m,n);
	cout<<"Ingrese datos:"<<endl;
	llenar_matriz(v,m,n);
	imprimir(v,m , n);	

	//------------segunda matriz----------------
	cout<<"Ingrese tamaño de la matriz 2"<<endl;	
	cin>>n>>o;
	crear_matriz(t,n,o);
	cout<<"Ingrese datos:"<<endl;
	llenar_matriz(t,n,o);
	imprimir(t,n,o);	
	
	// ----------- multiplicacion ---------------
	//matriz W= multiplicacion(v,m,n,t,o);
	matriz W= multiplicacion2(v,o,t);
	cout<<"Respuesta:"<<endl;
	imprimir(W,o,o);	

		
	return 0;
}

