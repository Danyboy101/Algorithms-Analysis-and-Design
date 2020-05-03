#include <iostream>
#include <queue>

using nam espace std;

int main()
{
  priority_queue<int> pq;
  int datos[] = {5, 4, 1, 2, 6, 3};
  int size = 6, k;

  cin >> k;

  for(int i = 0; i < 6; i++)
  {
    pq.push(datos[i]);
  }
  
  for(int i = 0; i < size; i++)
  {
    if(i + 1 == k)
    {
      cout << pq.top();
    }
    else
    {
      pq.pop();
    }
  }
}