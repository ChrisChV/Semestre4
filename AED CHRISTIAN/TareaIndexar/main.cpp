#include <iostream>
#include <Table.h>
#include "list"
#include "sad.h"

using namespace std;

int main()
{
    Table tt("datos.dat");
    Campo campo1;
    tt.del("1996");
    tt.del("2006");
    tt.del("1000");
    campo1.push_back("2007");
    campo1.push_back("F");
    campo1.push_back("1000");
    campo1.push_back("F77");
    tt.insert(campo1);
    campo1.clear();
    campo1.push_back("2008");
    campo1.push_back("F");
    campo1.push_back("1000");
    campo1.push_back("F77");
    tt.insert(campo1);

}
