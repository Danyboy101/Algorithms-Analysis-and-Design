//NOMBRE: Daniel Alejandro David Sánchez	
//MATRÍCULA: A00824566

#include <cstdlib>
#include <iostream>

using namespace std;

const int N = 21;

float datos4[9] = {0, 0.125, 0.125, 0.15, 0.12, 0.13, 0.25, 0.05, 0.05}; //la posición 0 no se ocupa.

float R[N][N];

//Problema 3
// Algoritmo de Gilbert y Moore


float minimo(int i, int j, float A[N][N], float R[N][N])
{
	float min = 10000000.0;
	int k;
	for (k = i; k <= j; k++)
	{
		if(A[i][k - 1] + A[k + 1][j] < min)
		{
			min = A[i][k - 1] + A[k + 1][j];
		}
	}

	R[i][j] = k;
	return min;	
}

float sumatoria(int i, int j, float p[])
{
	float sum = 0;
	for (int k = i; k <= j; k++)
	{
		sum += p[k];
	}
	
	return sum;
}


float gilbertymoore (float p[], int n)
{
	float A[N][N]; 
	// se considera que se usaron la columnas 0 a n y los renglones 1 a n+1 en la matriz		
	int j;
	
	for (int i = 1; i<= n; i++) 
	{ 
		A[i][i-1] = 0; A[i][i] = p[i];
  		R[i][i] = i; R[i][i-1] = 0; 
	}
	A[n+1][n] = 0;
	R[n+1][n] = 0;

	for (int diag = 1; diag <= n-1; diag++)
	  for (int i = 1; i <= n-diag; i++)
		{
			j = i+diag;
			A[i][j] = minimo(i, j, A, R) + sumatoria(i, j, p); 
			// calcula el valor mínimo entre los diversos valores de: 
			// A[i,k-1] + A[k+1, j] para k desde i hasta j.
			// La sumatoria calcula la suma de las probabilidades de la llave i hasta j
		}

	return A[1][n];
}


int main()
{
	cout << gilbertymoore(datos4, 9) << endl;
	for(int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			cout << R[i][j] << " ";
		}
		cout << endl;
	}              
	cout << endl;                                           
	system("pause");
}

