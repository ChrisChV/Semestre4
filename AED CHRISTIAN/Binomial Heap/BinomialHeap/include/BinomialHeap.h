#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H
#include "fstream"
#include "iostream"
#include "algorithm"

using namespace std;

template <typename T>
class BinomialHeap
{
    public:
        class Nodo{
            public:
                Nodo();
                Nodo(T);
                T valor;
                Nodo * padre;
                Nodo * hijo;
                Nodo * hermano;
                void destruirme();
                bool find(T valor, Nodo **&);
                void print(ofstream &);
                int _grado();
        };
        class Root{
            public:
                Root();
                Root(Nodo *);
                Nodo * contenido;
                Root * siguiente;
                int grado();
                void destruirme();
                void print(ofstream &);
        };
        BinomialHeap();
        BinomialHeap(string);
        void deleteRoot(Root **);
        BinomialHeap(bool, string);
        Root *getInicio();
        void print(string);
        void print(string, Root*&);
        void decreasekey(Nodo *);
        bool findTree(T valor, Root **&);
        bool find(T valor, Nodo **&);
        void deleteTree(T);
        void insert(T valor);
        void uni(Root *&);
        virtual ~BinomialHeap();
    protected:
    private:
        Root * inicio;
        bool animation;
        string name;
        void _merge(Root *&);
        void _intercambio(Root *, Root *);
        void _createHeap(BinomialHeap &, Nodo*);
};

void BinomialHeap::_createHeap(BinomialHeap & heap, Nodo * nodo){

}

void BinomialHeap::deleteRoot(Root **root){

}

void BinomialHeap::decreasekey(Nodo * nodo){
    while(nodo->padre){
        if(nodo->valor < nodo->padre->valor){
            swap(nodo->valor, nodo->padre->valor);
        }
        nodo = nodo->padre;
    }
}

void BinomialHeap::deleteRoot(Root **&root){

}

bool BinomialHeap::Nodo::find(T valor, Nodo **& nodo){
    if(this->valor == valor)return true;
    if(this->hermano){
        nodo = &(this->hermano);
        if(this->hermano->find(valor, nodo))return true;
    }
    if(this->hijo){
        nodo = &(this->hijo);
        if(this->hijo->find(valor, nodo))return true;
    }
    return false;
}

bool BinomialHeap::find(T valor, Nodo **& nodo){
    Root * iter = inicio;
    nodo = &(inicio->contenido);
    while(iter){
        if(iter->contenido->find(valor, nodo)) return true;
        iter = iter->siguiente;
        nodo = &(iter->contenido);
    }
    return false;
}

bool BinomialHeap::findTree(T valor, Root **&iter){
    iter = &inicio;
    while(*iter){
        if((*iter)->contenido->valor == valor) return true;
        iter = &((*iter)->siguiente);
    }
    return false;
}

void BinomialHeap::deleteTree(T valor){
    Root ** root;
    if(!findTree(valor, root))return;
    Root * temp =  *root;
    *root = (*root)->siguiente;
    temp->destruirme();
}

void BinomialHeap::insert(T valor){
    Root *nuevo = new Root(new Nodo(valor));
    uni(nuevo);
}

template <typename T>
void BinomialHeap<T>::Nodo::print(ofstream &archivo){
    archivo<<this->padre->valor<<"->"<<this->valor;
    if(this->hermano){
        this->hermano->print(archivo);
    }
    else return;
    if(this->hijo){
        this->hijo->print(archivo);
    }
}

template <typename T>
void BinomialHeap<T>::Root::print(ofstream &archivo){
    if(this->contenido->hijo){
        this->contenido->hijo->print(archivo);
    }
}

void BinomialHeap::print(string mensaje, Root *&secondInicio){
    cout<<mensaje<<endl;
    string nombreArchivo = name + ".dot";
    ofstream archivo(nombreArchivo);
    if(archivo.fail()){
        cout<<"ERROR->El archivo n ose pudo abrir";
        return;
    }
    archivo<<"digrapth{"<<endl;
    Root * temp = inicio;
    while(temp){
        temp->print(archivo);
        temp = temp->siguiente;
    }
    temp = secondInicio;
    while(temp){
        temp->print(archivo);
        temp = temp->siguiente;
    }
    archivo<<"}";
    archivo.close();
}

template <typename T>
void BinomialHeap<T>::print(string mensaje){
    cout<<mensaje<<endl;
    string nombreArchivo = name + ".dot";
    ofstream archivo(nombreArchivo);
    if(archivo.fail()){
        cout<<"ERROR->El archivo no se pudo abrir"<<endl;
        return;
    }
    archivo<<"digrapth{"<<endl;
    Root * temp = inicio;
    while(temp){
        temp->print(archivo);
        temp = temp->siguiente;
    }
    archivo<<"}";
    archivo.close();
}

template <typename T>
void BinomialHeap<T>::_merge(Root *&secondInicio){
    Root ** firstIter = this->inicio;
    Root ** secondIter = secondInicio;
    while(*secondIter){
        if(*firstIter == nullptr){
            *firstIter = *secondIter;
            (*firstIter)->siguiente = nullptr;
            firstIter = &((*firstIter)->siguiente);
            secondIter = &((*secondIter)->seguiente);
        }
        else if(*firstIter->grado() == *secondIter->grado()){
            auto temp = (*firstIter)->siguiente;
            (*firstIter)->siguiente = *secondIter;
            (*secondIter)->siguiente = temp;
            firstIter = &((*firstIter)->siguiente);
            secondIter = &((*secondIter)->siguiente);
        }
        else if(*firstIter->grado() > *secondIter->grado()){
            auto temp = (*firstIter);
            *firstIter = *secondIter;
            (*firstIter)->siguiente = temp->siguiente;
            firstIter = &((*firstIter)->siguiente->siguiente);
            secondIter = &((*secondIter)->siguiente);
        }
    }
}
///Intentar poner el delete
void BinomialHeap::_intervambio(Root *menor, Root *mayor){
    mayor->contenido->hermano = menor->contenido->hijo;
    menor->contenido->hijo = mayor->contenido;
    mayor->contenido->padre = menor->contenido;
}

template <typename T>
void BinomialHeap::uni(Root *&secondInicio){
    if(!secondInicio())return;
    _merge(secondInicio);
    Root * iter = inicio;
    Root * nextIter = inicio->siguiente;
    Root * prevIter = nullptr;
    while(nextIter){
        if(iter->grado() != nextIter->grado()){
            if(!prevIter)prevIter = inicio;
            nextIter = nextIter->siguiente;
            iter = iter->siguiente;
        }
        if(nextIter->siguiente->grado() == nextIter->grado()){
            if(!prevIter)prevIter = inicio;
            nextIter = nextIter->siguiente;
            iter = iter->siguiente;
        }
        ///ver si se puede hacer el delete
        if(iter->contenido->valor < nextIter->contenido->valor){
            _intervambio(iter, nextIter);
            if(prevIter) prevIter->siguiente = iter;
            iter->siguiente = nextIter->siguiente;
            nextIter = nextIter->siguiente;
        }
        else{
            _intervambio(nextIter, iter);
            if(prevIter) prevIter->siguiente = nextIter;
            iter = nextIter;
            nextIter = nextIter->siguiente;
        }
    }
}

template <typename T>
int BinomialHeap<T>::Nodo::_grado(){
    if(this->hijo)return this->hijo->_grado() + 1;
    return 0;
}

template <typename T>
int BinomialHeap<T>::Root::grado(){
    if(this->contenido->hijo)return this->contenido->hijo->_grado() + 1;
    return 0;
}

template <typename T>
void BinomialHeap<T>::Root::destruirme(){
    if(this->contenido->hijo)this->contenido->hijo->destruirme();
    if(this->siguiente)this->siguiente->destruirme();
    delete this;
}

template <typename T>
void BinomialHeap<T>::Nodo::destruirme(){
    if(this->hermano)this->hermano.destruirme();
    if(this->hijo)this->hijo.destruirme();
    delete this;
}

template <typename T>
BinomialHeap<T>::Root * BinomialHeap::getInicio(){return this->inicio;}

template <typename T>
BinomialHeap<T>::Root::Root(Nodo *contenido){
    this->contenido = contenido;
    siguiente = nullptr;
}

template <typename T>
BinomialHeap<T>::Root::Root(){
    contenido = nullptr;
    siguiente = nullptr;
}

template <typename T>
BinomialHeap<T>::Nodo::Nodo(T valor){
    this->valor = valor;
    padre = nullptr;
    hijo = nullptr;
    hermano = nullptr;
}

template <typename T>
BinomialHeap<T>::Nodo::Nodo(){
    padre = nullptr;
    hijo = nullptr;
    hermano = nullptr;
}

template <typename T>
BinomialHeap<T>::BinomialHeap(bool animation, string name){
    this->name = name;
    this->animation = animation;
    inicio = nullptr;
}

template <typename T>
BinomialHeap<T>::BinomialHeap(string name){
    this->name = name;
    animation = false;
    inicio = nullptr;
}

template <typename T>
BinomialHeap<T>::BinomialHeap(){
    name = "BinomialHeapDefault";
    inicio = nullptr;
    animation = false;
}

template <typename T>
BinomialHeap<T>::~BinomialHeap(){
    inicio->destruirme();
}
#endif // BINOMIALHEAP_H
