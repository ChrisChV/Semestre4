#include <iostream>
#include "fstream"
#include "list"
#include "fstream"
#include "Hombresito.h"

using namespace std;

int main()
{

    /*
    Hombresito *h = new Hombresito(70989549,true,'C');
    ofstream archivo("prueba/prueba.dat", ios::out | ios::binary | ios::app);
    cout<<"Pos Actual->"<<archivo.tellp()<<endl;
    archivo.write(reinterpret_cast<char *>(h),sizeof(Hombresito));
    archivo.close();
    */


    Hombresito *h;
    ifstream archivo("prueba/prueba.dat", ios::in | ios::binary);
    archivo.read(reinterpret_cast<char *>(&h),sizeof(Hombresito));
    h.print();

}

