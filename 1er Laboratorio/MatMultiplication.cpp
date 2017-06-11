/*Autor : EddyRene
Fecha: 25/03/2017
Laboratorio , Paralelos I 
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef vector<int> array;
typedef vector<vector<int> > matriz;

//#define SM (CLS / sizeof (double))

class M
{
	private:
		
		int a,b; // 
	public:	
		matriz v;
		M(){};

		void setValues(int f,int c){ a=f; b=c; }
		void criar()
		{
			v.resize(a);
			for(int i=0;i<a;i++)	
				v[i].resize(b);
		}
		void imprimir()
		{
			for(int i=0;i<a;i++)
			{
				for(int j=0;j<b;j++)
					cout<<v[i][j]<<"\t";
				cout<<endl;
			}
		}
		void encher_random(){
			for(int i=0;i<a;i++)
			{
				for(int j=0;j<b;j++){
					v[i][j]= rand() % 100;
				}
			}
		}
		void encher_ceros()
		{
			for(int i=0;i<a;i++)
			{
				for(int j=0;j<b;j++)
				{
					v[i][j]=0; 
				}
			}
		}
};

class Mtp
{
	private:
		int t=0;
	public:
		M A, B ,C;
		Mtp(){	}

		void ensaio(int w)
		{
			t=w;
			A.setValues(t,t);B.setValues(t,t);C.setValues(t,t);
			A.criar();B.criar();C.criar();
			A.encher_random();
			B.encher_random();	
			C.encher_ceros();
		}
		
		void m3bucles()
		{
			clock_t begin= clock();
			//cout<<t<<endl;
			for(int i=0;i<t;i++)
				for(int j=0;j<t;j++)
					for(int k=0;k<t;k++)
					{
						C.v[i][j]+=A.v[i][k]*B.v[k][j];
						//cout<<"entra"<<endl;
					}
			//cout<<"se termino con exito"<<endl;
			clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			cout<<"terminada 3 en: "<< time_spent<<endl;

		}
		void m6bucles()
		{
			int N=t;
			double SM=32;
			clock_t begin= clock();
			for (int i1 = 0; i1 < N/SM; i1 += SM)
				for (int j1 = 0; j1 < N/SM; j1 += SM)
					for ( int k1 = 0; k1 <N/SM; k1 += SM)
						for (int i = i1; i<i1+SM&&i<N;i++)
							for	(int j=j1;j<j1+SM&&j<N;j++)
								for	(int k=k1;k<k1+SM&&k<N;k++)
									C.v[i][j]+=A.v[i][k]*B.v[k][j];


			//cout<<"se termino con exito"<<endl;
			clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			cout<<"terminada 6  en: "<< time_spent<<endl;
		}
};

int main()
{
	cout<<"multiplicacao de matrizes"<<endl;
	Mtp p;
	int vezes = 0;
	int d =500;
	while (vezes < 1)
	{
		cout<<"prueba con matriz de dimension : "<<d << endl;
		p.ensaio(d);
		p.m3bucles();
		//p.m6bucles();
		d+=1000;
		vezes++;
	}
	return 0;
}