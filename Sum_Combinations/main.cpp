#include <iostream>
#include <vector>

using namespace std;

char sol[1000];

void sumComb(int n, int i, int acum, int total, int arr[])
{
  if(acum + total >= n && (acum == n || acum + arr[i + 1] <= n))
  {
    if(acum == n)
    {
      for(int k = 1; k < 1000; k++)
      { 
        if(sol[k] == 's')
        {
          cout << k << " ";
        }
      }
      cout << endl;
    }
    else
    {
      sol[i + 1] = 's';
      sumComb(n, i + 1, acum + arr[i + 1], total - arr[i + 1], arr);
      sol[i + 1] = 'n';
      sumComb(n, i + 1, acum, total - arr[i + 1], arr);
    }
  }
}

int main()
{
  int n, sum = 0;
  int arr[1000];

  for(int i = 1; i <= n; i++)
  {
    arr[i] = i;
    sum += i;
  }

  cin >> n;
  sol[0] = 'x';

  sumComb(n, 0, 0, sum, arr);
}