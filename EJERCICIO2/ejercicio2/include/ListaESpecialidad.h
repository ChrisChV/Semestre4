#ifndef LISTAESPECIALIDAD_H
#define LISTAESPECIALIDAD_H
#include "ColaPrioridad.h"

class ListaESpecialidad
{
    public:
        class Especialidad{
            public:
                Especialidad();
                Especialidad(string);
                string nombreEspecialidad;
                ColaPrioridad pacientes;
                Especialidad *siguiente;
        };
        ListaESpecialidad();
        void insertar(string);
        void print();
        bool find(string, Especialidad *&);
        void agregarPaciente(string, string, int);
        virtual ~ListaESpecialidad();
    protected:
    private:
        Especialidad *inicio;
        Especialidad *fin;
};

void ListaESpecialidad::print(){
    Especialidad * temp = inicio;
    while(temp){
        cout<<temp->nombreEspecialidad<<endl;
        temp = temp->siguiente;
    }
}

void ListaESpecialidad::agregarPaciente(string nombre, string especialidad, int gravedad){
    Especialidad * temp;
    if(!this->find(especialidad,temp))return;
    temp->pacientes.insertar(nombre, gravedad);
}

bool ListaESpecialidad::find(string nombre,Especialidad *&especialidad){
    especialidad = inicio;
    while(especialidad){
        if(especialidad->nombreEspecialidad == nombre)return true;
        especialidad = especialidad->siguiente;
    }
    return false;
}

void ListaESpecialidad::insertar(string nombre){
    Especialidad * nuevo = new Especialidad(nombre);
    if(inicio == nullptr){
        inicio = nuevo;
        fin = nuevo;
    }
    else{
        fin->siguiente = nuevo;
        fin = nuevo;
    }
}

ListaESpecialidad::Especialidad::Especialidad(string nombre){
    siguiente = nullptr;
    nombreEspecialidad = nombre;
}

ListaESpecialidad::Especialidad::Especialidad(){
    siguiente = nullptr;
    nombreEspecialidad = nullptr;
}

ListaESpecialidad::~ListaESpecialidad(){
}

ListaESpecialidad::ListaESpecialidad(){
    inicio = nullptr;
    fin = nullptr;
}

#endif // LISTAESPECIALIDAD_H
