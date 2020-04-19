#include <iostream>

using namespace std;

int main()
{
  int ones[100000], num;

  cin >> num;

  ones[0] = 0;

  for(int i = 1; i <= num; i++)
  {
    i % 2 == 0 ? ones[i] = ones[i / 2] : ones[i] = 1 + ones[i / 2];
  }

  cout << ones[num];
}