#include <iostream>
#include <Table.h>
#include "list"
#include "sad.h"

using namespace std;

int main()
{
    Table cursos("cursos.dat");
    Campo campo;
    cursos.find("INT",2,campo);
    for(auto iter = campo.begin(); iter != campo.end(); ++iter){
        cout<<*iter<<endl;
    }
}
