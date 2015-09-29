#include <iostream>
#include <algorithm>
#include "vector"
#include "ColaPrioridad.h"

using namespace std;

int main()
{
    ColaPrioridad pacientes;
    pacientes.insertar("Chris", 10);
    pacientes.insertar("Juan", 3);
    pacientes.insertar("Carlos", 1);
    pacientes.insertar("Ruben", 30);
    pacientes.insertar("Nicoll", 8);
    auto a = pacientes.size();
    for(int i = 0; i < a; i++){
        cout<<pacientes.pop()->nombrePaciente<<endl;
    }
}
