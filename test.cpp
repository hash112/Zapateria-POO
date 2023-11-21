#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>
#include <algorithm>

using namespace std;


class Test
{
    private:
        string test;

    public:
        Test(string _test)
        {
            test = _test;
        }

        void imp()
        {
            cout << test;
            Sleep(1000);
        }

        void callfun()
        {
            impfun();
        }
};

void impfun()
{
    cout << "Hola mundo";
}

int fun()
{
    Test test = Test("Hola mundo");
    test.callfun();
}

int printarr(int* a)
{
    for(int i=0; i<5; i++)
    {
        cout << a[i] << endl;
    }
    Sleep(2000);
}

int recuperarDeArchivo(int nZapato)
{
    vector <string> datosZapato;
    int numero_serie;
    fstream fin("zapatos.csv", ios::in);
    string temp, linea, dato;
    while(fin.eof() == 0)
    {
        datosZapato.clear();
        getline(fin, linea);
        cout << linea << endl;
        Sleep(2000);
        stringstream s(linea);
        while(getline(s, dato, ','))
        {
            datosZapato.push_back(dato);
        }
        numero_serie = stoi(datosZapato[0]);
        for(int i=0; i<6; i++)
        {
            if(i==5) cout << datosZapato[i] << endl;
            else cout << datosZapato[i] << " ";
        }
        if(numero_serie == nZapato)
        {
            fin.close();
            break;
        }
    }
    fin.close();
    return numero_serie;
}

int main(int argc, char **argv)
{
    fun();
}