#include <cstdlib>
#include <iostream>

using namespace std;

#define TAM 7

int costos[TAM][TAM] = {{ 0, 9999, 9999, 500, 9999, 9999, 100}, 
						{ 9999, 0, 345, 9999, 9999, 9999, 480}, 
						{ 340, 9999, 0, 9999, 9999, 222, 9999}, 
						{ 77, 9999, 9999, 0, 9999, 1075, 9999}, 
						{ 9999, 900, 900, 9999, 0, 9999, 9999}, 
						{ 9999, 9999, 760, 9999, 9999, 0, 120}, 
						{ 9999, 500, 9999, 9999, 230, 9999, 0}};

void despliegaMatriz (int m[TAM][TAM])
{ 
  for(int i=0;i<TAM;i++)
  {
    for(int j=0;j<TAM;j++)
      cout << m[i][j] << " ";
    cout << endl;
  }
}

int min(int a,int b)
{
 if(a<b)
  return(a);
 return(b);
}

void floyd(int p[TAM][TAM])
{
 for(int k=0;k<TAM;k++)
  for(int i=0;i<TAM;i++)
   for(int j=0;j<TAM;j++)
     p[i][j]=min(p[i][j],p[i][k]+p[k][j]);
}


int main()
{
    //Escribe aqui las llamadas para probar y responder el ejercicio
despliegaMatriz(costos);
	cout << "--------------\n";
	floyd(costos);
    	despliegaMatriz(costos);
    	cout<<"-----------\n";
    	system("pause");
}
