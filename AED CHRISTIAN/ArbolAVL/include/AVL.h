#ifndef AVL_H
#define AVL_H
#include "iostream"
#include "list"

using namespace std;

template <typename T>
class AVL
{
    public:
        class Nodo{
            public:
                Nodo();
                Nodo(T);
                T valor;
                int FE;
                Nodo * hijos[2];
                void eliminarme();
        };
        AVL();
        void printNiveles();
        void add(T valor);
        void RotacionSimple(Nodo *&, bool);
        void RotacionCompleja(Nodo *&, bool);
        virtual ~AVL();
    protected:
    private:
        bool _add(T valor, Nodo *&);
        Nodo * root;
};

template <typename T>
void AVL<T>::printNiveles(){
    if(!root)return;
    list<Nodo *> nodos;
    nodos.push_back(root);
    while(!nodos.empty()){
        list<Nodo *> temp;
        for(auto iter = nodos.begin(); iter != nodos.end(); ++iter){
            cout<<((*iter)->valor)<<":"<<(*iter)->FE<<"->";
            if((*iter)->hijos[0])temp.push_back((*iter)->hijos[0]);
            if((*iter)->hijos[1])temp.push_back((*iter)->hijos[1]);
        }
        cout<<endl;
        nodos = temp;
    }
}

template <typename T>
void AVL<T>::add(T valor){
    _add(valor, root);
}

template <typename T>
bool AVL<T>::_add(T valor, Nodo *& nodo){
    if(!nodo){
        nodo = new Nodo(valor);
        return true;
    }
    if(nodo->valor == valor)return false;
    if(!_add(valor, nodo->hijos[nodo->valor < valor]))return false;
    if(nodo->valor < valor)nodo->FE += 1;
    else nodo->FE -= 1;
    //nodo->FE += nodo->valor<valor?:-1;
    switch(nodo->FE){
        case 0:return false;
        case 2:
            if(nodo->hijos[1]->FE == 1){
                RotacionSimple(nodo,1);
                return false;
            }
            else{
                RotacionCompleja(nodo,1);
                return false;
            }
            break;
        case -2:
            if(nodo->hijos[0]->FE == -1){
                RotacionSimple(nodo,0);
                return false;
            }
            else{
                RotacionCompleja(nodo, 0);
                return false;
            }
            break;
    }
    return true;
}
template <typename T>
void AVL<T>::RotacionCompleja(Nodo *& one, bool flag){
    Nodo * two = one->hijos[flag];
    Nodo * three = two->hijos[!flag];
    one->hijos[flag] = three->hijos[!flag];
    one->hijos[!flag] = three->hijos[flag];
    three->hijos[!flag] = one;
    three->hijos[flag] = two;
    if(flag){
        switch(three->FE){
            case 0:one->FE = 0;two->FE = 0; break;
            case -1:one->FE = 1;two->FE = 0; break;
            case 1:one->FE = 0; two->FE = -1; break;
        }
    }
    else{
        switch(three->FE){
            case 0:one->FE = 0;two->FE = 0; break;
            case -1:one->FE = 0;two->FE = 1; break;
            case 1: one->FE = -1; two->FE = 0; break;
        }
    }
    one = three;
}


template <typename T>
void AVL<T>::RotacionSimple(Nodo *& one, bool flag){
    Nodo * two = one->hijos[flag];
    one->hijos[flag] = two->hijos[!flag];
    two->hijos[!flag] = one;
    one->FE = 0;
    two->FE = 0;
    one = two;
}

template <typename T>
AVL<T>::Nodo::Nodo(){
    FE = 0;
    hijos[0] = nullptr;
    hijos[1] = nullptr;
}

template <typename T>
AVL<T>::Nodo::Nodo(T valor){
    FE = 0;
    hijos[0] = nullptr;
    hijos[1] = nullptr;
    this->valor = valor;
}

template <typename T>
AVL<T>::AVL(){
    root = nullptr;
}

template <typename T>
void AVL<T>::Nodo::eliminarme(){
    if(!hijos[0] and !hijos[1]){
        delete this;
        return;
    }
    if(hijos[0])hijos[0]->eliminarme();
    else if(hijos[1])hijos[1]->eliminarme();
    delete this;
}

template <typename T>
AVL<T>::~AVL(){
    root->eliminarme();
}

#endif // AVL_H
