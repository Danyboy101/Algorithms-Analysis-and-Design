//Daniel Alejandro David Sánchez
//A00824566
//29/03/2020
//Variación del problema https://www.spoj.com/problems/CISTFILL/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

//Struct de la cisterna para poder almacenar sus valores
struct Cistern
{
    double height;
    double x, y, z;
};

//Función que resuelve el problema
void solve(vector<Cistern> cisterns, double waterVol, double vol, double low, double high)
{
    //Comparación para revisar que no exista un overflow, que ocurre cuando el volumne de agua es mayor
    //al volumen sumado de todas las cisternas
    if(waterVol > vol) 
    {
        cout << "OVERFLOW" << endl;
        return;
    }
    //Búsqueda binaria para encontrar el nivel máximo de agua
    while(high - low > 0.00000001) 
    {
        double mid = (low + high) / 2.0; //Cálculo para encontrar la mitad
        vol = 0.0;
        //Ciclo para verifficar que las cisternas estén dentro del rango que estamos buscando y también
        //para saber si sumar el volumen completo o solo una parte del volumen de la cisterna.
        for (int i = 0; i < cisterns.size(); i++)
        {
            if(mid > cisterns[i].height) //Comparación para saber si la cisterna está en el rango
            {
                if(cisterns[i].height + cisterns[i].z < mid)
                    vol += cisterns[i].x * cisterns[i].y * cisterns[i].z; //Cálculo del volumen completo
                else
                    vol += (mid - cisterns[i].height) * cisterns[i].x * cisterns[i].y; //Cálculo del volumen dentro del rango
            }
        }

        if(vol < waterVol)
            low = mid;
        else
            high = mid;
    }
    cout << fixed << setprecision(2) << low << endl; //Impresión del resultado
}

int main()
{
    char op1 = 's', op2 = 's';

    //Ciclo principal para un nuevo cálculo con una nueva red y un nuevo volumen de agua
    while(op2 == 's')
    {

        //Declaración de variables a utilizar
        int numCist;
        double waterVol, vol = 0, low = 100000000.0, high = -100000000.0;
        Cistern c;
        vector<Cistern> cisterns;

        cin >> numCist;

        //Ciclo para la lectura de las entradas del problema
        for (int i = 0; i < numCist; i++)
        {
            cin >> c.x >> c.y >> c.z >> c.height;
            vol += c.x * c.y * c.z;
            cisterns.push_back(c); //Push de cada struct de cisterna a un vector de cisternas
            if(c.height < low) low = c.height; //Comparación para determinar el límite inferior del binary search
            if(c.height + c.z > high) high = c.height + c.z; //Comparación para determinar el límite superior del binary search
        }
        
        cin >> waterVol;

        //Llamado a la función que resuelve el prblema
        solve(cisterns, waterVol, vol, low, high);

        cout << "Desea realizar otro calculo con la misma red? (s/n): ";
        cin >> op1;

        //Ciclo para repetir el cálculo con la misma red pero diferente volumen de agua
        while(op1 == 's')
        {
            cout << "Ingrese el nuevo volumen de agua: ";
            cin >> waterVol;

            //Llamado a la función que resuelve el prblema
            solve(cisterns, waterVol, vol, low, high);

            cout << "Desea realizar otro calculo con la misma red? (s/n): ";
            cin >> op1;
        }

        cout << "Desea realizar otro calculo con distinta red (s/n): ";
        cin >> op2;
    }
}