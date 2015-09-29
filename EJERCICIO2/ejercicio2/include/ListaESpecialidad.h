#ifndef LISTAESPECIALIDAD_H
#define LISTAESPECIALIDAD_H


class ListaESpecialidad
{
    public:
        class Especialidad{
            public:
                Especialidad();
                Especialidad(string);
                string nombreEspecialidad;
                Especialidad *siguiente;
        };
        ListaESpecialidad();
        void insertar(string);
        virtual ~ListaESpecialidad();
    protected:
    private:
        Especialidad *inicio;
        Especialidad *fin;
};

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
    nombreEspecialidad == nullptr;
}

ListaESpecialidad::~ListaESpecialidad(){
    inicio = nullptr;
    fin = nullptr;
}

ListaESpecialidad::ListaESpecialidad(){

}

#endif // LISTAESPECIALIDAD_H
