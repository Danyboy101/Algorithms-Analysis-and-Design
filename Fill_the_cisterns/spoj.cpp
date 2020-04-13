#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Cistern
{
    double height;
    double x, y, z;
};

void solve(vector<Cistern> cisterns, double waterVol, double vol, double low, double high)
{
    if(waterVol > vol) 
    {
        cout << "OVERFLOW" << endl;
        return;
    }
    
    while(high - low > 0.00000001) 
    {
        double mid = (low + high) / 2.0; 
        vol = 0.0;
        for (int i = 0; i < cisterns.size(); i++)
        {
            if(mid > cisterns[i].height) 
            {
                if(cisterns[i].height + cisterns[i].z < mid)
                    vol += cisterns[i].x * cisterns[i].y * cisterns[i].z; 
                else
                    vol += (mid - cisterns[i].height) * cisterns[i].x * cisterns[i].y; 
            }
        }

        if(vol < waterVol)
            low = mid;
        else
            high = mid;
    }
    cout << fixed << setprecision(2) << low << endl;
}

int main()
{
  int q;
  cin >> q;

  while(q--)
  {
    int numCist;
    double waterVol, vol = 0, low = 100000000.0, high = -100000000.0;
    Cistern c;
    vector<Cistern> cisterns;

    cin >> numCist;
    for (int i = 0; i < numCist; i++)
    {
      cin >> c.height >> c.z >> c.x >> c.y;
      vol += c.x * c.y * c.z;
      cisterns.push_back(c); 
      if(c.height < low) low = c.height; 
      if(c.height + c.z > high) high = c.height + c.z; 
    }
          
    cin >> waterVol;

    solve(cisterns, waterVol, vol, low, high);
  }
}