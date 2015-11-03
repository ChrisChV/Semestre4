#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H
#include "list"
#include "map"
#include "fstream"
#include "iostream"

enum Colores{SINCOLOR, NEGRO};

using namespace std;

template <typename T>
class FibonacciHeap
{
    public:
        class Nodo{
            public:
                Nodo();
                Nodo(T);
                list<Nodo*> hijos;
                T valor;
                Nodo * padre;
                bool color;
                void destruirme();
                void print(ofstream &archivo);
                typename list<Nodo *>::iterator _find(Nodo *);
                bool find(T,Nodo*&);
        };
        FibonacciHeap();
        void insert(T valor);
        T getMin();
        T popMin();
        void print();
        void decreaseKey(T,T);
        void consolidate();
        bool find(T,Nodo*&);
        virtual ~FibonacciHeap();
    protected:
    private:
        list<Nodo *> roots;
        Nodo * menor;
        typename list<Nodo *>::iterator _find(Nodo *menor);
        void verificarlLista(map<int,Nodo*>&,Nodo*);
        void verificarColor(Nodo*);
};

template <typename T>
T FibonacciHeap<T>::getMin(){
    return menor->valor;
}

template <typename T>
void FibonacciHeap<T>::verificarColor(Nodo *nodo){
    if(nodo->padre){
        if(nodo->padre->color == NEGRO){
            if(nodo->padre->padre){
                nodo->padre->padre->hijos.erase(nodo->padre->padre->_find((nodo->padre)));
                nodo->padre->color = SINCOLOR;
                roots.push_back(nodo->padre);
                verificarColor(nodo->padre);
                nodo->padre->padre = nullptr;
            }
        }
        else{
            nodo->padre->color = NEGRO;
        }
    }
}

template <typename T>
void FibonacciHeap<T>::decreaseKey(T valor, T nuevoValor){
    Nodo *nodo;
    if(!this->find(valor,nodo))return;
    nodo->valor = nuevoValor;
    if(menor->valor > nuevoValor) menor = nodo;
    nodo->padre->hijos.erase(nodo->padre->_find(nodo));
    roots.push_back(nodo);
    verificarColor(nodo);
    nodo->padre = nullptr;
}

template <typename T>
bool FibonacciHeap<T>::Nodo::find(T valor,Nodo *& nodo){
    if(this->valor == valor)return true;
    for(auto iter = hijos.begin(); iter != hijos.end(); ++iter){
        if((*iter)->valor == valor){
            nodo = (*iter);
            return true;
        }
        if((*iter)->find(valor,nodo))return true;
    }
    return false;
}

template <typename T>
bool FibonacciHeap<T>::find(T valor, Nodo *&nodo){
    for(auto iter = roots.begin(); iter != roots.end(); ++iter){
        if((*iter)->find(valor,nodo))return true;
    }
    return false;
}

template <typename T>
typename list<typename FibonacciHeap<T>::Nodo *>::iterator FibonacciHeap<T>::Nodo::_find(Nodo *nodo){
    for(auto iter = hijos.begin(); iter != hijos.end(); ++iter){
        if(*iter == nodo)return iter;
    }
    return hijos.end();
}

template <typename T>
typename list<typename FibonacciHeap<T>::Nodo *>::iterator FibonacciHeap<T>::_find(Nodo * menor){
    for(auto iter = roots.begin(); iter != roots.end(); ++iter){
        if(*iter == menor)return iter;
    }
    return roots.end();
}

template <typename T>
T FibonacciHeap<T>::popMin(){
    T resultado = menor->valor;
    for(auto iter = menor->hijos.begin(); iter != menor->hijos.end(); ++iter){
        (*iter)->padre = nullptr;
        roots.push_back(*iter);
    }
    roots.erase(_find(menor));
    menor->valor = 100000;
    consolidate();
    return resultado;
}

template <typename T>
void FibonacciHeap<T>::Nodo::print(ofstream &archivo){
    string c = "black";
    if(color == NEGRO) c = "red";
    archivo<<valor<<" [label = \""<<valor<<"\" color=\""<<c<<"\"];"<<endl;
    for(auto iter = hijos.begin(); iter != hijos.end(); ++iter){
        archivo<<valor<<"->"<<(*iter)->valor<<endl;
        (*iter)->print(archivo);
    }
}

template <typename T>
void FibonacciHeap<T>::print(){
    ofstream archivo("eje.dot");
    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir"<<endl;
        return;
    }
    archivo<<"digraph{"<<endl;
    for(auto iter = roots.begin(); iter != roots.end(); ++iter){
        (*iter)->print(archivo);
    }
    archivo<<"}";
    archivo.close();
    system("dot -Tpdf eje.dot -o eje.pdf");
}

template <typename T>
void FibonacciHeap<T>::verificarlLista(map<int,Nodo*> &lista, Nodo * iter){
    if(lista.find(iter->hijos.size()) == lista.end()){
        lista[iter->hijos.size()] = iter;
    }
    else if(lista[iter->hijos.size()] == nullptr){
        lista[iter->hijos.size()] = iter;
    }
    else{
        if(iter->valor < lista[iter->hijos.size()]->valor){
            int index = iter->hijos.size();
            iter->hijos.push_front(lista[index]);
            lista[index]->padre = iter;
            lista[index] = nullptr;
            verificarlLista(lista,iter);
        }
        else{
            int index = iter->hijos.size();
            lista[index]->hijos.push_front(iter);
            iter->padre = lista[index];
            Nodo * temp = lista[index];
            lista[index] = nullptr;
            verificarlLista(lista,temp);
        }
    }
}

template <typename T>
void FibonacciHeap<T>::consolidate(){
    map<int,Nodo *> lista;
    for(auto iter = roots.begin(); iter != roots.end(); ++iter){
        if(menor->valor > (*iter)->valor) menor = *iter;
        verificarlLista(lista,*iter);
    }
    list<Nodo *> tempList;
    for(auto iter = lista.begin(); iter != lista.end(); ++iter){
        if(iter->second) tempList.push_back(iter->second);
    }
    roots = tempList;
}

template <typename T>
void FibonacciHeap<T>::insert(T valor){
    Nodo *nodo;
    if(this->find(valor,nodo))return;
    Nodo *nuevo = new Nodo(valor);
    roots.push_back(nuevo);
    if(!menor or menor->valor > valor) menor = nuevo;
}

template <typename T>
void FibonacciHeap<T>::Nodo::destruirme(){
    for(auto iter = hijos.begin(); iter != hijos.end(); ++iter){
        (*iter)->destruirme();
    }
    delete this;
}

template <typename T>
FibonacciHeap<T>::Nodo::Nodo(T valor){
    this->valor = valor;
    padre = nullptr;
    color = SINCOLOR;
}

template <typename T>
FibonacciHeap<T>::Nodo::Nodo(){
    padre = nullptr;
    color = SINCOLOR;
}

template <typename T>
FibonacciHeap<T>::FibonacciHeap(){
    menor = nullptr;
}

template <typename T>
FibonacciHeap<T>::~FibonacciHeap(){
    for(auto iter = roots.begin(); iter != roots.end(); ++iter){
        (*iter)->destruirme();
    }
}

#endif // FIBONACCIHEAP_H
