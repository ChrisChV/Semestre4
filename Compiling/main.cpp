#include <iostream>
#include "fstream"
#include "list"
#include "vector"
#include "fstream"
#include "Hombresito.h"

using namespace std;

int main()
{
    vector<int> n;

    list<int> num;
    num.push_back(1);
    num.push_back(2);
    num.push_back(3);
    num.push_back(4);
    num.push_back(5);
    num.push_back(6);
    auto iter = num.begin();
    num.insert(iter,10);
    cout<<"Y"<<*iter<<endl;
    for(int i : num){
        cout<<i<<endl;
    }
    /*
    Hombresito *h = new Hombresito(70989549,true,'C');
    ofstream archivo("prueba/prueba.dat", ios::out | ios::binary | ios::app);
    cout<<"Pos Actual->"<<archivo.tellp()<<endl;
    archivo.write(reinterpret_cast<char *>(h),sizeof(Hombresito));
    archivo.close();
    */

    /*
    Hombresito *h;
    ifstream archivo("prueba/prueba.dat", ios::in | ios::binary);
    archivo.read(reinterpret_cast<char *>(&h),sizeof(Hombresito));
    h.print();
    */
}

