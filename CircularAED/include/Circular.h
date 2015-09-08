#ifndef CIRCULAR_H
#define CIRCULAR_H
#include "iostream"

using namespace std;

template <typename T>
class Circular
{
    public:
        class Nodo{
            public:
                Nodo();
                Nodo(T);
                T dato;
                Nodo * siguiente;
        };
        bool isEmpty();
        void insertar(T);
        void print();
        Circular();
        virtual ~Circular();
    protected:
    private:
        Nodo * cabeza;
        Nodo * cola;
        void _print(Nodo *&);
};

template<typename T>
void Circular<T>::insertar(T dato){
    Nodo * nuevo = new Nodo(dato);
    if(isEmpty()){
        cabeza = nuevo;
        cola = nuevo;
        nuevo->siguiente = nuevo;
    }
    else{
        cola->siguiente = nuevo;
        nuevo->siguiente = cabeza;
        cola = nuevo;
    }
}

template<typename T>
void Circular<T>::_print(Nodo *& nodo){
    if(nodo == cola){
        cout<<nodo->dato;
        return;
    }
    cout<<nodo->dato<<"->";
    _print(nodo->siguiente);
}

template<typename T>
void Circular<T>::print(){
    _print(cabeza);
}
template<typename T>
Circular<T>::~Circular(){

}

template<typename T>
bool Circular<T>::isEmpty(){
    if(cabeza == nullptr)
        return true;
    return false;
}



template<typename T>
Circular<T>::Nodo::Nodo(){
    siguiente = nullptr;
}
template<typename T>
Circular<T>::Nodo::Nodo(T dato){
    siguiente = nullptr;
    this->dato = dato;
}
template<typename T>
Circular<T>::Circular(){
    cabeza = nullptr;
    cola = nullptr;
}

#endif // CIRCULAR_H
