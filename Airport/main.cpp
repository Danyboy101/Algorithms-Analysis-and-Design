#include <iostream>
#include <climits>
#include <fstream>
#include <vector>

using namespace std;

void floyd(int mat[20][20], int p[20][20], int n)
{
  for(int k = 0; k < n; k++)
  {
    for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
      {
        if(mat[i][k] != INT_MAX && mat[k][j] != INT_MAX && mat[i][k] + mat[k][j] < mat[i][j])
        {
          mat[i][j] = mat[i][k] + mat[k][j];
          p[i][j] = k;
        }
      }
    }
  }
}

void initialize(int mat[20][20], int p[20][20])
{
  for(int i = 0; i < 20; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      if(i == j)
        mat[i][j] = 0;
      else
        mat[i][j] = INT_MAX;
      p[i][j] = 0;
    }
  }
}

int find(vector<string> v, string c)
{
  for (int i = 0; i < v.size(); i++)
  {
    if(v[i] == c) return i;
  }
  return -1;
}

void showPath(int pos1, int pos2, int p[20][20], vector<string> v)
{
  if(p[pos1][pos2] != 0)
  {
    showPath(pos1, p[pos1][pos2], p, v);
    cout << v[p[pos1][pos2]] << " -> ";
    showPath(p[pos1][pos2], pos2, p, v);
  }
}

void calcPath(int pos1, int pos2, int p[20][20], vector<string> v, int &legs)
{
  if(p[pos1][pos2] != 0)
  {
    showPath(pos1, p[pos1][pos2], p, v);
    legs++;
    showPath(p[pos1][pos2], pos2, p, v);
  }
}

void shortest(string c1, string c2, int mat[20][20], int p[20][20], vector<string> v)
{
  int pos1 = find(v, c1);
  int pos2 = find(v, c2);

  if(mat[pos1][pos2] != INT_MAX && mat[pos1][pos2] != 0)
  {
    cout << "Vuelo: " << c1 << " -> ";
    showPath(pos1, pos2, p, v);
    cout << c2 << " // Con costo de: " << mat[pos1][pos2] << endl;
  }
  else
  {
    cout << "No hay rutas disponibles" << endl;
  }
}

void allAvailable(string c1, int mat[20][20], int p[20][20], vector<string> v, int n)
{
  int i = 1;
  n--;
  int pos = find(v, c1);
  while(n--)
  {
    if(mat[pos][n] != 0 && mat[pos][n] != INT_MAX)
    {
      cout << "Vuelo " << i << ": " << c1 << " -> ";
      showPath(pos, n, p , v);
      cout << v[n] << " // Con costo de: " << mat[pos][n] ;
      cout << endl;
      i++;
    }
  }
}

void flightsWithLegs(int legs, int mat[20][20], int p[20][20], vector<string> v, int n)
{
  int x = 1;
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      int numLegs = 0;
      calcPath(i, j, p, v, numLegs);
      if(numLegs == legs && mat[i][j] != 0 && mat[i][j] != INT_MAX)
      {
        cout << "Vuelo " << x << ": " << v[i] << " -> ";
        showPath(i, j, p , v);
        cout << v[j] << " // Con costo de: " << mat[i][j] ;
        cout << endl;
        x++;
      }
    }
  }
}

int main()
{
  int ady[20][20], p[20][20], op, size = 0, legs;
  string fileName, city, aux = "", c1, c2, weight;
  ifstream file;
  vector<string> v;
  
  cout << "Ingrese el nombre del archivo: ";
  cin >> fileName;
  fileName += ".txt";
  file.open(fileName.c_str());

  initialize(ady, p);
  while(!file.eof())
  {
    if(aux == "#")
    {
      file >> c1 >> c2 >> weight;
      int pos1 = find(v, c1);
      int pos2 = find(v, c2);
      ady[pos1][pos2] = stoi(weight);
    }
    else
    {
      file >> city;
      size++;
      if(city != "#") v.push_back(city);
      else aux = city; 
    }
  }

  floyd(ady, p, size);

  cout << "Elija una opcion:" << endl;
  cout << "1. Ruta mas economica de x a y" << endl;
  cout << "2. Destinos posibles desde x" << endl;
  cout << "3. Destinos optimos con x escala" << endl;
  cin >> op;

  switch(op)
  {
  case 1:
    cout << "Ingrese el nombre de ambas ciudades" << endl;
    cout << "Ciudad 1: ";
    cin >> c1;
    cout << "Ciudad 2: ";
    cin >> c2;
    shortest(c1, c2, ady, p, v);
    break;
  case 2:
    cout << "Ingrese el nombre de la ciudad origen: ";
    cin >> c1;
    allAvailable(c1, ady, p, v, size);
    break;
  case 3:
    cout << "Ingrese numero de escalas: ";
    cin >> legs;
    flightsWithLegs(legs, ady, p, v, size);
    break;
  default:
    cout << "Opcion no valida" << endl;
    break;
  }

  file.close();
}