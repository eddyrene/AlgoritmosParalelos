#include <iostream>
#include <vector>

using namespace std;

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
matriz multiplicacion( matriz &A,int m,int n, matriz &B ,int o)
{
	matriz C;
	crear_matriz(C,m,o);
	llenar_ceros(C,m,o);			
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			for(int k=0;k<o;k++)
				C[i][j]=C[i][j]+A[i][k]*B[k][j];

	return C;
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
	matriz W= multiplicacion(v,m,n,t,o);
	cout>>"Respuesta:"<<endl;
	imprimir(W,m,o);	

		
	return 0;
}

